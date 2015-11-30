#include "linkcontext.h"

LinkContext::LinkContext(QObject *parent) :
    QAbstractListModel(parent)
{
}

LinkContext::~LinkContext()
{

}

QVariant LinkContext::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

int LinkContext::rowCount(const QModelIndex &parent) const
{
    return linkTypes.size();
}

QVariant LinkContext::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole){
        int row = index.row();
        return linkTypes[row];
    }
    else
        return QVariant();
}

void LinkContext::addLinkType(const QString &name)
{
    beginInsertRows(QModelIndex(), linkTypes.size(), linkTypes.size());
    linkTypes.append(name);
    endInsertRows();
}

void LinkContext::removeLinkType(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    beginRemoveRows(QModelIndex(), index.row(), index.row());
    linkTypes.remove(index.row());
    endRemoveRows();
}

void LinkContext::renameLinkType(const QModelIndex &index, const QString &newName)
{
    if(!index.isValid())
        return;

    linkTypes[index.row()] = newName;
    emit dataChanged(index, index);
}
