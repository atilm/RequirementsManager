#include "requirementsview.h"
#include <iostream>
using namespace std;

RequirementsView::RequirementsView(QWidget *parent) :
    QTreeView(parent)
{
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::InternalMove);
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

void RequirementsView::startDrag(Qt::DropActions supportedActions)
{
    currentlyDragged = selectionModel()->currentIndex();

    QTreeView::startDrag(supportedActions);
}

void RequirementsView::dropEvent(QDropEvent *event)
{
    QModelIndex destination = indexAt(event->pos());

    requirementsModel()->moveRequirement(currentlyDragged, destination);

    event->accept();
}

RequirementsModel *RequirementsView::requirementsModel()
{
    return static_cast<RequirementsModel*>(model());
}
