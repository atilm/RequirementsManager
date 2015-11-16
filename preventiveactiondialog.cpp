#include "preventiveactiondialog.h"
#include "ui_preventiveactiondialog.h"

PreventiveActionDialog::PreventiveActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreventiveActionDialog)
{
    ui->setupUi(this);
    model = nullptr;
    setWindowTitle(tr("Preventive Action"));
}

PreventiveActionDialog::~PreventiveActionDialog()
{
    delete ui;
}

void PreventiveActionDialog::injectWidgets(QLineEditAdapter *testCaseEdit,
                                           QLineEditAdapter *testNameEdit,
                                           QLineEditAdapter *shortDescriptionEdit,
                                           QPlainTextEditAdapter *preparationEdit,
                                           QPlainTextEditAdapter *actionEdit,
                                           QPlainTextEditAdapter *expectedResultEdit)
{
    int index, row, col, rowSpan, colSpan;

    this->testCaseEdit = testCaseEdit;
    index = ui->verticalLayout->indexOf(ui->testCaseEdit);
    delete ui->testCaseEdit;
    ui->testCaseEdit = testCaseEdit;
    ui->verticalLayout->insertWidget(index, testCaseEdit);

    this->testNameEdit = testNameEdit;
    index = ui->verticalLayout->indexOf(ui->testNameEdit);
    delete ui->testNameEdit;
    ui->testNameEdit = testNameEdit;
    ui->verticalLayout->insertWidget(index, testNameEdit);

    this->shortDescriptionEdit = shortDescriptionEdit;
    index = ui->verticalLayout->indexOf(ui->shortDescriptionEdit);
    delete ui->shortDescriptionEdit;
    ui->shortDescriptionEdit = shortDescriptionEdit;
    ui->verticalLayout->insertWidget(index, shortDescriptionEdit);

    this->preparationEdit = preparationEdit;
    index = ui->gridLayout->indexOf(ui->preparationEdit);
    ui->gridLayout->getItemPosition(index, &row, &col, &rowSpan, &colSpan);
    delete ui->preparationEdit;
    ui->preparationEdit = preparationEdit;
    ui->gridLayout->addWidget(preparationEdit, row, col, rowSpan, colSpan);

    this->actionEdit = actionEdit;
    index = ui->gridLayout->indexOf(ui->actionEdit);
    ui->gridLayout->getItemPosition(index, &row, &col, &rowSpan, &colSpan);
    delete ui->actionEdit;
    ui->actionEdit = actionEdit;
    ui->gridLayout->addWidget(actionEdit, row, col, rowSpan, colSpan);

    this->expectedResultEdit = expectedResultEdit;
    index = ui->gridLayout->indexOf(ui->expectedResultEdit);
    ui->gridLayout->getItemPosition(index, &row, &col, &rowSpan, &colSpan);
    delete ui->expectedResultEdit;
    ui->expectedResultEdit = expectedResultEdit;
    ui->gridLayout->addWidget(expectedResultEdit, row, col, rowSpan, colSpan);
}

void PreventiveActionDialog::setModel(PreventiveActionModel *model)
{
    this->model = model;
}

int PreventiveActionDialog::exec(const QModelIndex &index)
{
    setCurrentIndex(index);
    return QDialog::exec();
}

void PreventiveActionDialog::accept()
{
    currentAction->setTestCase(testCaseEdit->text());
    currentAction->setTestName(testNameEdit->text());
    currentAction->setShortDescription(shortDescriptionEdit->text());
    currentAction->setPreparation(preparationEdit->toPlainText());
    currentAction->setAction(actionEdit->toPlainText());
    currentAction->setExpectedResult(expectedResultEdit->toPlainText());
    QDialog::accept();
}

void PreventiveActionDialog::setCurrentIndex(const QModelIndex &index)
{
    if(!model)
        return;

    currentAction = model->getAction(index);
    testCaseEdit->setText(currentAction->getTestCase());
    testNameEdit->setText(currentAction->getTestName());
    shortDescriptionEdit->setText(currentAction->getShortDescription());
    preparationEdit->setPlainText(currentAction->getPreparation());
    actionEdit->setPlainText(currentAction->getAction());
    expectedResultEdit->setPlainText(currentAction->getExpectedResult());
}
