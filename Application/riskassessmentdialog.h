#ifndef RISKASSESSMENTDIALOG_H
#define RISKASSESSMENTDIALOG_H

#include <QDialog>
#include "riskmodel.h"
#include "riskassessmenttable.h"
#include "qplaintexteditadapter.h"
#include "riskassessmentmodel.h"

namespace Ui {
class RiskAssessmentDialog;
}

class RiskAssessmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RiskAssessmentDialog(QPlainTextEditAdapter *scenarioEdit,
                                  QPlainTextEditAdapter *mitigationStrategyEdit,
                                  RiskAssessmentTable *initialRiskEdit,
                                  RiskAssessmentTable *finalRiskEdit,
                                  QWidget *parent = 0);
    ~RiskAssessmentDialog();

    void setModel(RiskAssessmentModel *model);

public slots:
    virtual int exec(const QModelIndex &index);
    virtual void accept();

private:
    Ui::RiskAssessmentDialog *ui;
    QPlainTextEditAdapter *scenarioEdit;
    QPlainTextEditAdapter *mitigationStrategyEdit;
    RiskAssessmentTable *initialRiskEdit;
    RiskAssessmentTable *finalRiskEdit;
    RiskAssessmentModel *model;
    RiskAssessment *currentRA;

    void injectWidgets(QPlainTextEditAdapter *scenarioEdit,
                       QPlainTextEditAdapter *mitigationStrategyEdit,
                       RiskAssessmentTable *initialRiskEdit,
                       RiskAssessmentTable *finalRiskEdit);

    void setCurrentIndex(const QModelIndex &index);
};

#endif // RISKASSESSMENTDIALOG_H
