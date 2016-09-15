#include "requirementsview.h"
#include <QAction>
#include <QDebug>

RequirementsView::RequirementsView(QMessageBoxProvider *msg, QMenu *contextMenu, QWidget *parent) :
    QTreeView(parent)
{
    setExpandsOnDoubleClick(false);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::InternalMove);

    setUpContextMenu(contextMenu);
    this->msg = msg;
}

RequirementsView::~RequirementsView()
{
    delete msg;
}

void RequirementsView::setModel(shared_ptr<RequirementsModel> model)
{
    QTreeView::setModel(model.get());

    connect(model.get(), SIGNAL(columnsChanged()), this, SLOT(resizeColumns()));
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
    {
        selectionModel()->setCurrentIndex(newIdx, QItemSelectionModel::ClearAndSelect);
    }
}

void RequirementsView::appendChild(Requirement *item)
{
    QModelIndex newIdx = requirementsModel()->insertChild(item, selectionModel()->currentIndex(), -1);

    if(newIdx.isValid())
    {
        setExpanded(selectionModel()->currentIndex(), true);

        if(!item->isReference())
        {
            selectionModel()->setCurrentIndex(newIdx, QItemSelectionModel::ClearAndSelect);
        }
    }
}

void RequirementsView::removeCurrent()
{
    if(selectionModel()->currentIndex().isValid())
    {
        QMessageBox::StandardButton answer = msg->showQuestion(this, tr("Delete requirement"), tr("Delete the current requirement?"));

        if(answer == QMessageBox::Yes)
        {
            requirementsModel()->removeRequirement(selectionModel()->currentIndex());
        }
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

bool RequirementsView::edit(const QModelIndex &index,
                            QAbstractItemView::EditTrigger trigger,
                            QEvent *event)
{
    if(!index.isValid())
    {
        return false;
    }

    if(!requirementsModel()->getRequirement(index)->isReference())
    {
        return QTreeView::edit(index, trigger, event);
    }
    else
    {
        return false;
    }
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
    contextMenu->addSeparator();
    contextMenu->addAction(tr("Create Reference"), this, SLOT(handleCreateReference()));

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

void RequirementsView::handleCreateReference()
{
    QModelIndex newIdx = requirementsModel()->createReferenceTo(currentIndex());

    if(newIdx.isValid())
    {
        selectionModel()->setCurrentIndex(newIdx, QItemSelectionModel::ClearAndSelect);
    }
}
