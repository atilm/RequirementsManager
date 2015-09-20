#include "requirementsview.h"
#include <iostream>
using namespace std;

RequirementsView::RequirementsView(QWidget *parent) :
    QTreeView(parent)
{
}

void RequirementsView::insertSibling()
{
//    QModelIndexList selectedRows = selectionModel()->selectedRows();

//    if(selectedRows.isEmpty())
//        requirementsModel()->appendChild(QModelIndex());
//    else
//        requirementsModel()->appendSibling(selectedRows.first());

    requirementsModel()->appendSibling(selectionModel()->currentIndex());
}

void RequirementsView::appendChild()
{
//    QModelIndexList selectedRows = selectionModel()->selectedRows();

//    if(selectedRows.isEmpty())
//        requirementsModel()->appendChild(QModelIndex());
//    else
//        requirementsModel()->appendChild(selectedRows.first());

    requirementsModel()->appendChild(selectionModel()->currentIndex());
}

void RequirementsView::removeCurrent()
{
    QModelIndexList selectedRows = selectionModel()->selectedRows();
    if(!selectedRows.empty()){
        requirementsModel()->removeRequirement(selectedRows.first());
    }
}

RequirementsModel *RequirementsView::requirementsModel()
{
    return static_cast<RequirementsModel*>(model());
}
