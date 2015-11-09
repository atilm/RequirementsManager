#include "riskassessmenteditcontroller.h"

RiskAssessmentEditController::RiskAssessmentEditController(RiskAssessmentDialog *dialog) :
    QObject(0)
{
    riskModel = nullptr;
    riskView = nullptr;
    this->dialog = dialog;
}

RiskAssessmentEditController::~RiskAssessmentEditController()
{
    delete dialog;
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

void RiskAssessmentEditController::currentRequirementChanged(const QModelIndex &current, const QModelIndex &previous)
{
    riskModel = reqModel->getRiskAssessment(current);
    riskView->setModel(riskModel);
    dialog->setModel(riskModel);
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

void RiskAssessmentEditController::editRiskAssessment(const QModelIndex &index)
{
    if(!riskModel)
        return;

    dialog->exec(index);
}
