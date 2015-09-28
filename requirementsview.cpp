#include "requirementsview.h"
#include <iostream>
using namespace std;

RequirementsView::RequirementsView(QWidget *parent) :
    QTreeView(parent)
{
}

void RequirementsView::insertSibling()
{
    QModelIndex newIdx = requirementsModel()->appendSibling(selectionModel()->currentIndex());

    if(newIdx.isValid())
        selectionModel()->setCurrentIndex(newIdx, QItemSelectionModel::ClearAndSelect);
}

void RequirementsView::appendChild()
{
    QModelIndex newIdx = requirementsModel()->appendChild(selectionModel()->currentIndex());

    if(newIdx.isValid())
        selectionModel()->setCurrentIndex(newIdx, QItemSelectionModel::ClearAndSelect);
}

void RequirementsView::removeCurrent()
{
    if(selectionModel()->currentIndex().isValid()){
        requirementsModel()->removeRequirement(selectionModel()->currentIndex());
    }
}

RequirementsModel *RequirementsView::requirementsModel()
{
    return static_cast<RequirementsModel*>(model());
}
