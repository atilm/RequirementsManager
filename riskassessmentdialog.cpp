#include "riskassessmentdialog.h"
#include "ui_riskassessmentdialog.h"

RiskAssessmentDialog::RiskAssessmentDialog(QPlainTextEditAdapter *scenarioEdit,
                                           RiskAssessmentTable *initialRiskEdit,
                                           RiskAssessmentTable *finalRiskEdit,
                                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RiskAssessmentDialog)
{
    model = nullptr;
    ui->setupUi(this);
    setWindowTitle(tr("Risk Assessment"));

    injectWidgets(scenarioEdit, initialRiskEdit, finalRiskEdit);
}

RiskAssessmentDialog::~RiskAssessmentDialog()
{
    delete ui;
}

void RiskAssessmentDialog::setModel(RiskAssessmentModel *model)
{
    this->model = model;
}

int RiskAssessmentDialog::exec(const QModelIndex &index)
{
    setCurrentIndex(index);
    return QDialog::exec();
}

void RiskAssessmentDialog::accept()
{
    currentRA->setScenario(scenarioEdit->toPlainText());
    QDialog::accept();
}

void RiskAssessmentDialog::injectWidgets(QPlainTextEditAdapter *scenarioEdit,
                                         RiskAssessmentTable *initialRiskEdit,
                                         RiskAssessmentTable *finalRiskEdit)
{
    int index, row, col, rowSpan, colSpan;

    this->scenarioEdit = scenarioEdit;
    index = ui->gridLayout->indexOf(ui->scenarioTextEdit);
    ui->gridLayout->getItemPosition(index, &row, &col, &rowSpan, &colSpan);
    delete ui->scenarioTextEdit;
    ui->scenarioTextEdit = scenarioEdit;
    ui->gridLayout->addWidget(scenarioEdit, row, col, rowSpan, colSpan);
    ui->scenarioTextEdit->setMinimumWidth(400);
    ui->scenarioTextEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    this->initialRiskEdit = initialRiskEdit;
    index = ui->gridLayout->indexOf(ui->initialRiskTable);
    ui->gridLayout->getItemPosition(index, &row, &col, &rowSpan, &colSpan);
    delete ui->initialRiskTable;
    ui->initialRiskTable = initialRiskEdit;
    ui->gridLayout->addWidget(initialRiskEdit, row, col, rowSpan, colSpan);
    ui->initialRiskTable->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    this->finalRiskEdit = finalRiskEdit;
    index = ui->gridLayout->indexOf(ui->finalRiskTable);
    ui->gridLayout->getItemPosition(index, &row, &col, &rowSpan, &colSpan);
    delete ui->finalRiskTable;
    ui->finalRiskTable = finalRiskEdit;
    ui->gridLayout->addWidget(finalRiskEdit, row, col, rowSpan, colSpan);
    ui->finalRiskTable->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    RiskModel *model = new RiskModel();
    initialRiskEdit->setModel(model);
    finalRiskEdit->setModel(model);
}

void RiskAssessmentDialog::setCurrentIndex(const QModelIndex &index)
{
    if(!model)
        return;

    currentRA = model->getRiskAssessment(index);
    scenarioEdit->setPlainText(currentRA->scenario());
}
