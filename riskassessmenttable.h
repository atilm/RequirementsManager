#ifndef RISKASSESSMENTTABLE_H
#define RISKASSESSMENTTABLE_H

#include <QWidget>
#include "riskmodel.h"

namespace Ui {
class RiskAssessmentTable;
}

class RiskAssessmentTable : public QWidget
{
    Q_OBJECT

public:
    explicit RiskAssessmentTable(QWidget *parent = 0);
    virtual ~RiskAssessmentTable();

    virtual void setModel(RiskModel *model);

private:
    Ui::RiskAssessmentTable *ui;
};

#endif // RISKASSESSMENTTABLE_H
