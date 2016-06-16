#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "requirementsview.h"
#include <QCloseEvent>

MainWindow::MainWindow(ProjectFileController *fileController, RequirementsModel *requirements,
                       RichTextController *richText, FileStateTracker *fileState,
                       QMessageBoxProvider *messageBox, AppSettings *settings,
                       AttributeEditor *attributeDialog,
                       RiskAssessmentEditController *riskAssessmentEditController,
                       LinkTypeEditor *linkTypeEditor, LinkController *linkController,
                       SourceCodeController *sourceController, SettingsDialog *settingsDialog,
                       ReportController *reportController,
                       QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    applicationName = "Requirements Manager";
    setWindowTitle(applicationName);

    setSplitterBehaviour();

    this->settings = settings;
    this->messageBox = messageBox;
    this->fileState = fileState;
    this->fileController = fileController;
    this->requirements = requirements;
    this->attributeDialog = attributeDialog;
    this->riskAssessmentEditController = riskAssessmentEditController;
    this->linkTypeEditor = linkTypeEditor;
    this->linkController = linkController;
    this->settingsDialog = settingsDialog;

    linkController->setLinkView(ui->linkView);
    linkController->setAddButton(ui->addLinksButton);
    linkController->setRemoveButton(ui->removeLinkButton);

    this->sourceController = sourceController;
    this->sourceController->injectViews(ui->moduleListView,
                                        ui->functionListView,
                                        ui->testListView);

    fileController->setModel(requirements);

    this->richText = richText;

    richText->setItalicAction(ui->actionItalic);
    richText->setBoldAction(ui->actionBold);
    richText->setCodeAction(ui->actionCode);
    richText->setBulletAction(ui->actionBulletList);
    richText->setInsertImageAction(ui->actionInsertImage);

    this->reportController = reportController;
    reportController->setModel(requirements );

    connect(ui->actionProjectSettings, SIGNAL(triggered()), settingsDialog, SLOT(exec()));
    connect(ui->actionLinkTypes, SIGNAL(triggered()), linkTypeEditor, SLOT(exec()));
    connect(ui->actionAttributes, SIGNAL(triggered()), attributeDialog, SLOT(exec()));
    connect(ui->actionSave, SIGNAL(triggered()), fileController, SLOT(save()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), fileController, SLOT(saveAs()));
    connect(ui->actionOpen, SIGNAL(triggered()), fileController, SLOT(load()));
    connect(ui->actionReport, SIGNAL(triggered()), reportController, SLOT(generateReport()));
    connect(fileState, SIGNAL(filePathChanged(QString)), this, SLOT(handleFilePathChanged(QString)));
    connect(fileState, SIGNAL(changedStateChanged(bool)), this, SLOT(handleChangedStateChanged(bool)));
    connect(fileController, SIGNAL(fileLoaded()), sourceController, SLOT(parseProjectCode()));
}

MainWindow::~MainWindow()
{
    delete fileController;
    delete requirements;
    delete richText;
    delete descriptionView;
    delete requirementsView;
    delete messageBox;
    delete settings;
    delete attributeDialog;
    delete riskAssessmentEditController;
    delete linkTypeEditor;
    delete sourceController;
    delete reportController;
    delete ui;
}

void MainWindow::injectViews(RequirementsView *requirementsView, DescriptionView *descriptionView)
{
    this->requirementsView = requirementsView;
    delete ui->treeView;
    ui->treeView = requirementsView;
    ui->splitter->insertWidget(0, requirementsView);

    requirementsView->setModel(requirements);
    connect(ui->actionAddSibling, SIGNAL(triggered()),
            requirementsView, SLOT(insertSibling()));
    connect(ui->actionAddChild, SIGNAL(triggered()),
            requirementsView, SLOT(appendChild()));
    connect(ui->actionRemoveRequirement, SIGNAL(triggered()),
            requirementsView, SLOT(removeCurrent()));

    descriptionView->setModel(requirements);
    this->descriptionView = descriptionView;
    delete ui->textEdit;
    ui->textEdit = descriptionView;
    ui->splitter->insertWidget(1, descriptionView);

    richText->setTextEdit(descriptionView);

    connect(requirementsView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            descriptionView, SLOT(switchItem(QModelIndex,QModelIndex)));
    connect(requirementsView, SIGNAL(clicked(QModelIndex)),
            descriptionView, SLOT(showItem(QModelIndex)));
    connect(fileController, SIGNAL(fileLoaded()),
            requirementsView, SLOT(resizeColumns()));

    linkController->setDescriptionView(descriptionView);
    linkController->setUpSelectionModeConnections();

    sourceController->injectDescriptionView(descriptionView);
    sourceController->injectRequirementsView(requirementsView);

    setSplitterBehaviour();
}

void MainWindow::injectRiskViews(RiskDescriptionView *riskDescriptionView,
                                 RiskTableView *riskTableView,
                                 PreventiveActionTableView *preventiveActionTableView)
{
    int index;

    this->riskDescriptionView = riskDescriptionView;
    index = ui->riskDescVLayout->indexOf(ui->riskDescriptionView);
    delete ui->riskDescriptionView;
    ui->riskDescriptionView = riskDescriptionView;
    ui->riskDescVLayout->insertWidget(index, riskDescriptionView);

    this->riskTableView = riskTableView;
    index = ui->riskVLayout->indexOf(ui->riskView);
    delete ui->riskView;
    ui->riskView = riskTableView;
    ui->riskVLayout->insertWidget(index, riskTableView);

    this->preventiveActionTableView = preventiveActionTableView;
    index = ui->preventiveActionVLayout->indexOf(ui->preventiveActionView);
    delete ui->preventiveActionView;
    ui->preventiveActionView = preventiveActionTableView;
    ui->preventiveActionVLayout->insertWidget(index, preventiveActionTableView);

    riskAssessmentEditController->setRequirementsModel(requirements);
    riskAssessmentEditController->setRequirementsView(requirementsView);
    riskAssessmentEditController->setRiskView(riskTableView);
    riskAssessmentEditController->setDescriptionView(riskDescriptionView);
    riskAssessmentEditController->setAddRiskButton(ui->addRiskButton);
    riskAssessmentEditController->setRemoveRiskButton(ui->removeRiskButton);
    riskAssessmentEditController->setActionView(preventiveActionTableView);
    riskAssessmentEditController->setAddActionButton(ui->addPreventiveActionButton);
    riskAssessmentEditController->setRemoveActionButton(ui->removePreventiveActionButton);

    sourceController->injectRiskDescriptionView(riskDescriptionView);
    sourceController->injectPreventiveActionView(preventiveActionTableView);

    setSplitterBehaviour();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    fileController->askSaveUnsavedChanges();
    settings->save();
    e->accept();
}

void MainWindow::handleFilePathChanged(const QString &fPath)
{
    setWindowTitle(applicationName + " - " + fPath);
}

void MainWindow::handleChangedStateChanged(bool unsavedChanges)
{
    QString windowTitle = applicationName + " - " + fileState->filePath();
    if(unsavedChanges)
        windowTitle += "*";

    setWindowTitle(windowTitle);
}

void MainWindow::setSplitterBehaviour()
{
    ui->splitter->setStretchFactor(0,0);
    ui->splitter->setStretchFactor(1,1);
    ui->riskLayoutHSplitter->setStretchFactor(0,0);
    ui->riskLayoutHSplitter->setStretchFactor(1,1);
    ui->splitter_3->setStretchFactor(0,1);
    ui->splitter_3->setStretchFactor(1,0);
    ui->splitter_2->setStretchFactor(0,0);
    ui->splitter_2->setStretchFactor(1,0);

    QList<int> sizes;
    sizes << 500 << 200;
    ui->splitter_2->setSizes(sizes);
}



