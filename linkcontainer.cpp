#include "linkcontainer.h"

LinkContainer::LinkContainer(LinkContext *context, QObject *parent)
    : QAbstractItemModel(parent)
{
    this->context = context;
}

LinkContainer::~LinkContainer()
{

}

int LinkContainer::columnCount(const QModelIndex &parent) const
{
    return 1;
}

int LinkContainer::rowCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant LinkContainer::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QModelIndex LinkContainer::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex LinkContainer::parent(const QModelIndex &index) const
{
    return QModelIndex();
}
