#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "requirementsview.h"
#include <QCloseEvent>

MainWindow::MainWindow(ProjectFileController *fileController, RequirementsModel *requirements,
                       RichTextController *richText, FileStateTracker *fileState,
                       QMessageBoxProvider *messageBox, AppSettings *settings,
                       AttributeEditor *attributeDialog, RiskAssessmentDialog *riskAssessmentDialog,
                       QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    applicationName = "Requirements Manager";
    setWindowTitle(applicationName);

    this->settings = settings;
    this->messageBox = messageBox;
    this->fileState = fileState;
    this->fileController = fileController;
    this->requirements = requirements;
    this->attributeDialog = attributeDialog;
    this->riskAssessmentDialog = riskAssessmentDialog;

    fileController->setModel(requirements);

    this->richText = richText;

    richText->setTextEdit(ui->textEdit);
    richText->setItalicAction(ui->actionItalic);
    richText->setBoldAction(ui->actionBold);
    richText->setBulletAction(ui->actionBulletList);

    connect(ui->addRiskButton, SIGNAL(clicked()), riskAssessmentDialog, SLOT(show()));
    connect(ui->actionAttributes, SIGNAL(triggered()), this, SLOT(handleEditAttributes()));
    connect(ui->actionSave, SIGNAL(triggered()), fileController, SLOT(save()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), fileController, SLOT(saveAs()));
    connect(ui->actionOpen, SIGNAL(triggered()), fileController, SLOT(load()));
    connect(fileState, SIGNAL(filePathChanged(QString)), this, SLOT(handleFilePathChanged(QString)));
    connect(fileState, SIGNAL(changedStateChanged(bool)), this, SLOT(handleChangedStateChanged(bool)));
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

void MainWindow::handleEditAttributes()
{
    attributeDialog->exec();
}

