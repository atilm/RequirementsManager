#ifndef RISKASSESSMENTEDITCONTROLLER_H
#define RISKASSESSMENTEDITCONTROLLER_H

#include <QObject>
#include <QToolButton>

#include "requirementsmodel.h"
#include "requirementsview.h"
#include "riskassessmentmodel.h"
#include "riskassessmentdialog.h"
#include "risktableview.h"
#include "preventiveactiontableview.h"

class RiskAssessmentEditController : public QObject
{
    Q_OBJECT
public:
    RiskAssessmentEditController(RiskAssessmentDialog *dialog);
    virtual ~RiskAssessmentEditController();

    virtual void setRequirementsModel(RequirementsModel *requirements);
    virtual void setRequirementsView(RequirementsView *reqView);
    virtual void setRiskModel(RiskAssessmentModel *riskModel);
    virtual void setRiskView(RiskTableView *riskView);
    virtual void setAddRiskButton(QToolButton *addRiskButton);
    virtual void setRemoveRiskButton(QToolButton *removeRiskButton);
    virtual void setActionView(PreventiveActionTableView *actionView);
    virtual void setAddActionButton(QToolButton *addActionButton);
    virtual void setRemoveActionButton(QToolButton *removeActionButton);

public slots:
    virtual void currentRequirementChanged(const QModelIndex &current, const QModelIndex &previous);
    virtual void currentRiskChanged(const QModelIndex &current, const QModelIndex &previous);
    virtual void insertBeforeCurrent();
    virtual void removeCurrent();
    virtual void insertActionBeforeCurrent();
    virtual void removeCurrentAction();
    virtual void editRiskAssessment(const QModelIndex &index);

private:
    RequirementsModel *reqModel;
    RequirementsView *reqView;
    RiskAssessmentModel *riskModel;
    RiskTableView *riskView;
    RiskAssessmentDialog *dialog;
    PreventiveActionModel *actionModel;
    PreventiveActionTableView *actionView;

};

#endif // RISKASSESSMENTEDITCONTROLLER_H
