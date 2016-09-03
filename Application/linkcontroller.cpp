#include "linkcontroller.h"
#include "linktorequirement.h"
#include <QDebug>

LinkController::LinkController(QObject *parent)
    : QObject(parent)
{

}

LinkController::~LinkController()
{

}

void LinkController::setLinkView(QTreeView *view)
{
    this->linkView = view;
}

void LinkController::setRequirementsView(RequirementsView *view)
{
    this->reqView = view;
}

void LinkController::setDescriptionView(DescriptionView *view)
{
    this->descriptionView = view;
}

void LinkController::setAddButton(QToolButton *button)
{
    this->addButton = button;

    connect(addButton, SIGNAL(toggled(bool)),
            this, SLOT(handleAddButtonToggled(bool)));
}

void LinkController::setRemoveButton(QToolButton *button)
{
    this->removeButton = button;
    connect(removeButton, SIGNAL(clicked()),
            this, SLOT(handleRemoveButtonClicked()));
}

void LinkController::setUpSelectionModeConnections()
{
    reqView->setEditTriggers(QAbstractItemView::DoubleClicked |
                             QAbstractItemView::EditKeyPressed);
    disconnect(reqView, SIGNAL(doubleClicked(QModelIndex)),
               this, SLOT(handleAddRequirementLink(QModelIndex)));
    connect(reqView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(handleCurrentRequirementChanged(QModelIndex, QModelIndex)));
}

void LinkController::setUpAddModeConnections()
{
    reqView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    disconnect(reqView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(handleCurrentRequirementChanged(QModelIndex, QModelIndex)));
    connect(reqView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(handleAddRequirementLink(QModelIndex)));
}

void LinkController::handleCurrentRequirementChanged(const QModelIndex &current,
                                                     const QModelIndex &)
{
    RequirementsModel *model = static_cast<RequirementsModel*>(reqView->model());
    try{
        currentLinks = model->getLinkContainer(current);
        linkView->setModel(currentLinks);
        linkView->expandToDepth(1);
    }
    catch(const InvalidIndexException &){
        linkView->setModel(nullptr);
    }
}

void LinkController::handleAddButtonToggled(bool on)
{
    if(on)
        setUpAddModeConnections();
    else
        setUpSelectionModeConnections();
}

void LinkController::handleRemoveButtonClicked()
{
    QModelIndex current = linkView->selectionModel()->currentIndex();
    currentLinks->removeLink(current);
}

void LinkController::handleAddRequirementLink(const QModelIndex &index)
{
    QModelIndex current = linkView->selectionModel()->currentIndex();
    RequirementsModel *model = static_cast<RequirementsModel*>(reqView->model());
    Requirement *req = model->getRequirement(index);
    LinkToRequirement *link = new LinkToRequirement(req->getID());

    currentLinks->addLink(current, link);
}

