#ifndef RISKASSESSMENTDIALOG_H
#define RISKASSESSMENTDIALOG_H

#include <QDialog>

namespace Ui {
class RiskAssessmentDialog;
}

class RiskAssessmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RiskAssessmentDialog(QWidget *parent = 0);
    ~RiskAssessmentDialog();

private:
    Ui::RiskAssessmentDialog *ui;
};

#endif // RISKASSESSMENTDIALOG_H
