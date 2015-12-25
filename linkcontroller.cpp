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

