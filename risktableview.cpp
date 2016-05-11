#include "risktableview.h"

RiskTableView::RiskTableView(QWidget *parent) :
    QTableView(parent)
{
    requirements = nullptr;
}

RiskTableView::~RiskTableView()
{
}

void RiskTableView::setRequirementsModel(RequirementsModel *requirements)
{
    this->requirements = requirements;
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
        ra->add(selectionModel()->currentIndex().row());
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
