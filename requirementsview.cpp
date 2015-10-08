#include "requirementsview.h"
#include <QAction>

RequirementsView::RequirementsView(QMenu *contextMenu, QWidget *parent) :
    QTreeView(parent)
{
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::InternalMove);

    setUpContextMenu(contextMenu);
}

void RequirementsView::setModel(RequirementsModel *model)
{
    QTreeView::setModel(model);

    connect(model, SIGNAL(columnsChanged()), this, SLOT(resizeColumns()));
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

void RequirementsView::resizeColumns()
{
    for(int c=0;c < model()->columnCount();c++)
        resizeColumnToContents(c);
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

void RequirementsView::setUpContextMenu(QMenu *contextMenu)
{
    this->contextMenu = contextMenu;

    contextMenu->addAction(tr("User Requirement"), this, SLOT(handleToUserRequirement()));
    contextMenu->addAction(tr("Functional Requirement"), this, SLOT(handleToFunctionalRequirement()));
    contextMenu->addAction(tr("Design Requirement"), this, SLOT(handleToDesignRequirement()));

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(handleCustomContextMenu(QPoint)));
}

void RequirementsView::handleCustomContextMenu(QPoint point)
{
    QModelIndex index = indexAt(point);
    if (index.isValid()) {
        contextMenu->exec(mapToGlobal(point));
    }
}

void RequirementsView::handleToUserRequirement()
{
    requirementsModel()->setType(currentIndex(), Requirement::UserRequirement);
}

void RequirementsView::handleToFunctionalRequirement()
{
    requirementsModel()->setType(currentIndex(), Requirement::FunctionalRequirement);
}

void RequirementsView::handleToDesignRequirement()
{
    requirementsModel()->setType(currentIndex(), Requirement::DesignRequirement);
}
