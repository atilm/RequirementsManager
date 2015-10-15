#include "riskassessmenttable.h"
#include "ui_riskassessmenttable.h"

RiskAssessmentTable::RiskAssessmentTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RiskAssessmentTable)
{
    ui->setupUi(this);
}

RiskAssessmentTable::~RiskAssessmentTable()
{
    delete ui;
}
