#include "risktableview.h"

RiskTableView::RiskTableView(QWidget *parent) :
    QTableView(parent)
{
}

RiskTableView::~RiskTableView()
{
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
