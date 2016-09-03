#include "preventiveactiontableview.h"

PreventiveActionTableView::PreventiveActionTableView(QWidget *parent) :
    QTableView(parent)
{
}

PreventiveActionTableView::~PreventiveActionTableView()
{

}

void PreventiveActionTableView::appendTestReference(shared_ptr<AutomatedTestReference> testRef)
{
    PreventiveActionModel *testModel = static_cast<PreventiveActionModel*>(model());

    if(testModel){
        testModel->appendReference(testRef);
    }
}


