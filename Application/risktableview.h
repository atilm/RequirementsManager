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

    //virtual void setRequirementsModel(RequirementsModel *requirements);

signals:

public slots:
    //virtual void currentRequirementChanged(const QModelIndex &current, const QModelIndex &previous);
    virtual void insertBeforeCurrent();
    virtual void removeCurrent();

private:
    //RequirementsModel *requirements;

    RiskAssessmentModel* riskAssessmentModel();
};

#endif // RISKTABLEVIEW_H
