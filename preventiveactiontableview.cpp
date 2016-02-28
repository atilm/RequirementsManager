#include "preventiveactiontableview.h"

PreventiveActionTableView::PreventiveActionTableView(QWidget *parent) :
    QTableView(parent)
{
    setFont(QFont("Verdana", 11, QFont::Normal));
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


