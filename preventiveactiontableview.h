#ifndef PREVENTIVEACTIONTABLEVIEW_H
#define PREVENTIVEACTIONTABLEVIEW_H

#include <QTableView>
#include "requirementsmodel.h"
#include "riskassessmentmodel.h"
#include "risktableview.h"
#include "preventiveactionmodel.h"

class PreventiveActionTableView : public QTableView
{
    Q_OBJECT
public:
    explicit PreventiveActionTableView(QWidget *parent = 0);
    virtual ~PreventiveActionTableView();

    virtual void setRequirementModel(RequirementsModel *requirements);
    virtual void setRiskTableView(RiskTableView *riskView);

signals:

public slots:
    virtual void currentRequirementChanged(const QModelIndex &current, const QModelIndex &previous);
    virtual void currentRiskChanged(const QModelIndex &current, const QModelIndex &previous);
    virtual void insertBeforeCurrent();
    virtual void removeCurrent();

private:
    RequirementsModel *requirements;
    RiskAssessmentModel *risks;
    RiskTableView *riskView;

    PreventiveActionModel* preventiveActionModel();
};

#endif // PREVENTIVEACTIONTABLEVIEW_H
