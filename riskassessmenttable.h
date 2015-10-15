#ifndef RISKASSESSMENTTABLE_H
#define RISKASSESSMENTTABLE_H

#include <QWidget>

namespace Ui {
class RiskAssessmentTable;
}

class RiskAssessmentTable : public QWidget
{
    Q_OBJECT

public:
    explicit RiskAssessmentTable(QWidget *parent = 0);
    virtual ~RiskAssessmentTable();

private:
    Ui::RiskAssessmentTable *ui;
};

#endif // RISKASSESSMENTTABLE_H
