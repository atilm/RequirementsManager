#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(RequirementsModel *requirements,
                       RichTextController *richText,
                       QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Requirements Manager");

    this->requirements = requirements;
    this->richText = richText;
    richText->setTextEdit(ui->textEdit);
    richText->setItalicAction(ui->actionItalic);
    richText->setBoldAction(ui->actionBold);
    richText->setBulletAction(ui->actionBulletList);
}

MainWindow::~MainWindow()
{
    delete requirements;
    delete richText;
    delete descriptionView;
    delete requirementsView;
    delete ui;
}

void MainWindow::injectViews(RequirementsView *requirementsView, DescriptionView *descriptionView)
{
    this->requirementsView = requirementsView;
    delete ui->treeView;
    ui->treeView = requirementsView;
    ui->splitter->insertWidget(0, requirementsView);

    requirementsView->setModel(requirements);

    this->descriptionView = descriptionView;
    delete ui->textEdit;
    ui->textEdit = descriptionView;
    ui->splitter->insertWidget(1, descriptionView);
}
