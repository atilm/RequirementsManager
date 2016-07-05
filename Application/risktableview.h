#ifndef RISKTABLEVIEW_H
#define RISKTABLEVIEW_H

#include <QTableView>
#include "riskassessmentmodel.h"


class RiskTableView : public QTableView
{
    Q_OBJECT
public:
    explicit RiskTableView(QWidget *parent = 0);
    virtual ~RiskTableView();

signals:

public slots:
    virtual void insertBeforeCurrent();
    virtual void removeCurrent();

private:
    RiskAssessmentModel* riskAssessmentModel();
};

#endif // RISKTABLEVIEW_H
