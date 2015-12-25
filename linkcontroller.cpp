#include "linkcontroller.h"
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

void LinkController::setUpConnections()
{
    connect(reqView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(handleCurrentRequirementChanged(QModelIndex, QModelIndex)));
}

void LinkController::handleCurrentRequirementChanged(const QModelIndex &current,
                                                     const QModelIndex &previous)
{
    RequirementsModel *model = static_cast<RequirementsModel*>(reqView->model());
    linkView->setModel(model->getLinkContainer(current));
}

void LinkController::handleAddButtonToggled(bool on)
{
    if(on){
        reqView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
    else{
        reqView->setEditTriggers(QAbstractItemView::DoubleClicked |
                                 QAbstractItemView::EditKeyPressed);
    }
}

void LinkController::handleRemoveButtonClicked()
{

}

