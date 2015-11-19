#include "riskassessmenteditcontroller.h"

RiskAssessmentEditController::RiskAssessmentEditController(RiskAssessmentDialog *dialog, PreventiveActionDialog *actionDialog) :
    QObject(0)
{
    riskModel = nullptr;
    riskView = nullptr;
    this->dialog = dialog;
    this->actionDialog = actionDialog;
}

RiskAssessmentEditController::~RiskAssessmentEditController()
{
    delete dialog;
    delete actionDialog;
}

void RiskAssessmentEditController::setRequirementsModel(RequirementsModel *requirements)
{
    this->reqModel = requirements;
}

void RiskAssessmentEditController::setRequirementsView(RequirementsView *reqView)
{
    this->reqView = reqView;
    connect(reqView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(currentRequirementChanged(QModelIndex,QModelIndex)));
}

void RiskAssessmentEditController::setRiskModel(RiskAssessmentModel *model)
{
    this->riskModel = model;
    dialog->setModel(model);
}

void RiskAssessmentEditController::setRiskView(RiskTableView *view)
{
    this->riskView = view;
    connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editRiskAssessment(QModelIndex)));
}

void RiskAssessmentEditController::setAddRiskButton(QToolButton *addRiskButton)
{
    connect(addRiskButton, SIGNAL(clicked()), this, SLOT(insertBeforeCurrent()));
}

void RiskAssessmentEditController::setRemoveRiskButton(QToolButton *removeRiskButton)
{
    connect(removeRiskButton, SIGNAL(clicked()), this, SLOT(removeCurrent()));
}

void RiskAssessmentEditController::setActionView(PreventiveActionTableView *actionView)
{
    this->actionView = actionView;
    connect(actionView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editPreventiveAction(QModelIndex)));
}

void RiskAssessmentEditController::setAddActionButton(QToolButton *addActionButton)
{
    connect(addActionButton, SIGNAL(clicked()), this, SLOT(insertActionBeforeCurrent()));
}

void RiskAssessmentEditController::setRemoveActionButton(QToolButton *removeActionButton)
{
    connect(removeActionButton, SIGNAL(clicked()), this, SLOT(removeCurrentAction()));
}

void RiskAssessmentEditController::setDescriptionView(RiskDescriptionView *descriptionView)
{
    this->descriptionView = descriptionView;
    descriptionView->setReadOnly(true);
}

void RiskAssessmentEditController::currentRequirementChanged(const QModelIndex &current, const QModelIndex &previous)
{
    riskModel = reqModel->getRiskAssessment(current);
    riskView->setModel(riskModel);
    dialog->setModel(riskModel);
    actionView->setModel(nullptr);
    connect(riskView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(currentRiskChanged(QModelIndex,QModelIndex)));
}

void RiskAssessmentEditController::currentRiskChanged(const QModelIndex &current, const QModelIndex &previous)
{
    actionModel = riskModel->getPreventiveActions(current);
    actionView->setModel(actionModel);
    actionDialog->setModel(actionModel);
    connect(actionView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(currentActionChanged(QModelIndex, QModelIndex)));
}

void RiskAssessmentEditController::currentActionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    PreventiveAction *a = actionModel->getAction(current);
    descriptionView->displayAction(a);
}

void RiskAssessmentEditController::insertBeforeCurrent()
{
    if(!riskModel)
        return;

//    QModelIndex newIndex = riskModel->add(riskView->currentIndex());
//    dialog->exec(newIndex);
    riskModel->add(riskView->currentIndex());
}

void RiskAssessmentEditController::removeCurrent()
{
    if(riskModel)
        riskModel->remove(riskView->currentIndex());
}

void RiskAssessmentEditController::insertActionBeforeCurrent()
{
    if(!actionModel)
        return;

    actionModel->add(actionView->currentIndex());
}

void RiskAssessmentEditController::removeCurrentAction()
{
    if(actionModel)
        actionModel->remove(actionView->currentIndex());
}

void RiskAssessmentEditController::editRiskAssessment(const QModelIndex &index)
{
    if(!riskModel)
        return;

    dialog->exec(index);
}

void RiskAssessmentEditController::editPreventiveAction(const QModelIndex &index)
{
    if(!actionModel)
        return;

    actionDialog->exec(index);
}
