#include "preventiveactiontableview.h"

PreventiveActionTableView::PreventiveActionTableView(QWidget *parent) :
    QTableView(parent)
{
}

PreventiveActionTableView::~PreventiveActionTableView()
{

}

void PreventiveActionTableView::appendTestReference(AutomatedTestReference *testRef)
{
    PreventiveActionModel *testModel = static_cast<PreventiveActionModel*>(model());

    if(testModel){
        testModel->appendReference(testRef);
    }
}

