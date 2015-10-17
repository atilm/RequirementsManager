#ifndef RISKASSESSMENTDIALOG_H
#define RISKASSESSMENTDIALOG_H

#include <QDialog>
#include "riskmodel.h"
#include "riskassessmenttable.h"
#include "qplaintexteditadapter.h"

namespace Ui {
class RiskAssessmentDialog;
}

class RiskAssessmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RiskAssessmentDialog(QPlainTextEditAdapter *scenarioEdit,
                                  RiskAssessmentTable *initialRiskEdit,
                                  RiskAssessmentTable *finalRiskEdit,
                                  QWidget *parent = 0);
    ~RiskAssessmentDialog();

private:
    Ui::RiskAssessmentDialog *ui;
    QPlainTextEditAdapter *scenarioEdit;
    RiskAssessmentTable *initialRiskEdit;
    RiskAssessmentTable *finalRiskEdit;

    void injectWidgets(QPlainTextEditAdapter *scenarioEdit,
                       RiskAssessmentTable *initialRiskEdit,
                       RiskAssessmentTable *finalRiskEdit);
};

#endif // RISKASSESSMENTDIALOG_H
