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
#include "preventiveactiondialog.h"
#include "riskdescriptionview.h"

#include <memory>
using namespace std;

class RiskAssessmentEditController : public QObject
{
    Q_OBJECT
public:
    RiskAssessmentEditController(RiskAssessmentDialog *dialog,
                                 PreventiveActionDialog *actionDialog);
    virtual ~RiskAssessmentEditController();

    virtual void setRequirementsModel(shared_ptr<RequirementsModel> requirements);
    virtual void setRequirementsView(RequirementsView *reqView);
    virtual void setRiskModel(shared_ptr<RiskAssessmentModel> riskModel);
    virtual void setRiskView(RiskTableView *riskView);
    virtual void setAddRiskButton(QToolButton *addRiskButton);
    virtual void setRemoveRiskButton(QToolButton *removeRiskButton);
    virtual void setActionView(PreventiveActionTableView *actionView);
    virtual void setAddActionButton(QToolButton *addActionButton);
    virtual void setRemoveActionButton(QToolButton *removeActionButton);
    virtual void setDescriptionView(RiskDescriptionView *descriptionView);

public slots:
    virtual void currentRequirementChanged(const QModelIndex &current, const QModelIndex &);
    virtual void currentRiskChanged(const QModelIndex &current, const QModelIndex &);
    virtual void currentActionChanged(const QModelIndex &current, const QModelIndex &);
    virtual void insertBeforeCurrent();
    virtual void removeCurrent();
    virtual void insertActionBeforeCurrent();
    virtual void removeCurrentAction();
    virtual void editRiskAssessment(const QModelIndex &index);
    virtual void editPreventiveAction(const QModelIndex &index);
    virtual void actionClicked(const QModelIndex &index);
    virtual void riskClicked(const QModelIndex &index);
    virtual void handleFileLoad();

private:
    shared_ptr<RequirementsModel> reqModel;
    RequirementsView *reqView;
    shared_ptr<RiskAssessmentModel> riskModel;
    RiskTableView *riskView;
    RiskAssessmentDialog *dialog;
    PreventiveActionDialog *actionDialog;
    shared_ptr<PreventiveActionModel> actionModel;
    PreventiveActionTableView *actionView;
    RiskDescriptionView *descriptionView;
};

#endif // RISKASSESSMENTEDITCONTROLLER_H
