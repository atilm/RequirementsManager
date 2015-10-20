#include "risktableview.h"

RiskTableView::RiskTableView(RiskAssessmentEditController *editController,
                             QWidget *parent) :
    QTableView(parent)
{
    requirements = nullptr;
    this->editController = editController;
}

RiskTableView::~RiskTableView()
{
    delete editController;
}

void RiskTableView::setRequirementsModel(RequirementsModel *requirements)
{
    this->requirements = requirements;
}

void RiskTableView::setEditController(RiskAssessmentEditController *editController)
{
    this->editController = editController;
}

void RiskTableView::currentRequirementChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if(requirements){
        try{
            setModel(requirements->getRiskAssessment(current));
        }
        catch(...){

        }
    }
}

void RiskTableView::insertBeforeCurrent()
{
    RiskAssessmentModel *ra = riskAssessmentModel();

    if(ra)
        ra->add(selectionModel()->currentIndex());
}

void RiskTableView::removeCurrent()
{
    RiskAssessmentModel *ra = riskAssessmentModel();

    if(ra)
        ra->remove(selectionModel()->currentIndex());
}

RiskAssessmentModel* RiskTableView::riskAssessmentModel()
{
    return dynamic_cast<RiskAssessmentModel*>(model());
}
