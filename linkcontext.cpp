#include "linkcontext.h"

LinkContext::LinkContext(QObject *parent) :
    QAbstractListModel(parent)
{
}

LinkContext::~LinkContext()
{

}

void LinkContext::clear()
{
    int rows = rowCount();

    for(int i=0;i<rows;i++)
        removeLinkType(index(0,0));
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

QString LinkContext::typeName(int index) const
{
    if(isValidIndex(index))
        return linkTypes[index];
}

void LinkContext::addLinkType(const QString &name)
{
    beginInsertRows(QModelIndex(), linkTypes.size(), linkTypes.size());
    linkTypes.append(name);
    endInsertRows();
    emit newLinkType(linkTypes.count()-1);
}

void LinkContext::removeLinkType(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    beginRemoveRows(QModelIndex(), index.row(), index.row());
    linkTypes.remove(index.row());
    endRemoveRows();
    emit linkTypeRemoved(index.row());
}

void LinkContext::renameLinkType(const QModelIndex &index, const QString &newName)
{
    if(!index.isValid())
        return;

    linkTypes[index.row()] = newName;
    emit dataChanged(index, index);
}

bool LinkContext::isValidIndex(int index) const
{
    if(index < linkTypes.count() && index >= 0)
        return true;
    else
        return false;
}
