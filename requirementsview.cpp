#include "requirementsview.h"

RequirementsView::RequirementsView(QWidget *parent) :
    QTreeView(parent)
{
}

void RequirementsView::insertSibling()
{
    QModelIndexList selectedRows = selectionModel()->selectedRows();

    if(selectedRows.isEmpty())
        requirementsModel()->appendSibling(QModelIndex());
    else
        requirementsModel()->appendSibling(selectedRows.first());
}

void RequirementsView::appendChild()
{
    QModelIndexList selectedRows = selectionModel()->selectedRows();

    if(selectedRows.isEmpty())
        requirementsModel()->appendChild(QModelIndex());
    else
        requirementsModel()->appendChild(selectedRows.first());
}

RequirementsModel *RequirementsView::requirementsModel()
{
    return static_cast<RequirementsModel*>(model());
}
