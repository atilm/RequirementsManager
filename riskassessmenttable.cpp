#include "riskassessmenttable.h"
#include "ui_riskassessmenttable.h"

RiskAssessmentTable::RiskAssessmentTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RiskAssessmentTable)
{
    ui->setupUi(this);
    setMinimumWidth(555);
    setMinimumHeight(190);
}

RiskAssessmentTable::~RiskAssessmentTable()
{
    delete ui;
}
