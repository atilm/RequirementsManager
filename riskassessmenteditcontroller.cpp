#include "riskassessmenteditcontroller.h"

RiskAssessmentEditController::RiskAssessmentEditController(RiskAssessmentDialog *dialog) :
    QObject(0)
{
    model = nullptr;
    view = nullptr;
    this->dialog = dialog;
}

RiskAssessmentEditController::~RiskAssessmentEditController()
{
    delete dialog;
}

void RiskAssessmentEditController::setModel(RiskAssessmentModel *model)
{
    this->model = model;
    dialog->setModel(model);
}

void RiskAssessmentEditController::setView(RiskTableView *view)
{
    this->model = view;
}

void RiskAssessmentEditController::insertBeforeCurrent()
{
    if(!model)
        return;

    QModelIndex newIndex = model->add(view->currentIndex());
    dialog->exec(newIndex);
}

void RiskAssessmentEditController::removeCurrent()
{
    if(model)
        model->remove(view->currentIndex());
}

void RiskAssessmentEditController::editCurrent()
{
    if(!model)
        return;

    dialog->exec(view->currentIndex());
}
