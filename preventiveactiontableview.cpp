#include "preventiveactiontableview.h"
#include <iostream>
using namespace std;

PreventiveActionTableView::PreventiveActionTableView(QWidget *parent) :
    QTableView(parent)
{
    risks = nullptr;
}

PreventiveActionTableView::~PreventiveActionTableView()
{

}

void PreventiveActionTableView::setRequirementModel(RequirementsModel *requirements)
{
    this->requirements = requirements;
}

void PreventiveActionTableView::setRiskTableView(RiskTableView *riskView)
{
    this->riskView = riskView;
}

void PreventiveActionTableView::currentRequirementChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if(requirements){
        try{
            risks = requirements->getRiskAssessment(current);
            connect(riskView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                    this, SLOT(currentRiskChanged(QModelIndex,QModelIndex)));
        }
        catch(...){

        }
    }
}

void PreventiveActionTableView::currentRiskChanged(const QModelIndex &current, const QModelIndex &previous)
{
    cout << "risk changed" << endl;
    if(risks){
        try{
            setModel(risks->getPreventiveActions(current));
        }
        catch(...){
            cout << "exception" << endl;
        }
    }
}

void PreventiveActionTableView::insertBeforeCurrent()
{
    PreventiveActionModel *pa = preventiveActionModel();

    if(pa)
        pa->add(selectionModel()->currentIndex());
}

void PreventiveActionTableView::removeCurrent()
{
    PreventiveActionModel *pa = preventiveActionModel();

    if(pa)
        pa->remove(selectionModel()->currentIndex());
}

PreventiveActionModel *PreventiveActionTableView::preventiveActionModel()
{
    return dynamic_cast<PreventiveActionModel*>(model());
}
