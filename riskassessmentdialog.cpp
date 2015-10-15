#include "riskassessmentdialog.h"
#include "ui_riskassessmentdialog.h"

RiskAssessmentDialog::RiskAssessmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RiskAssessmentDialog)
{
    ui->setupUi(this);
}

RiskAssessmentDialog::~RiskAssessmentDialog()
{
    delete ui;
}
