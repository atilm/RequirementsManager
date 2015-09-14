#include "requirementsmodel.h"
#include <iostream>
using namespace std;

RequirementsModel::RequirementsModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    root = new Requirement();
    root->appendChild();
}

int RequirementsModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

int RequirementsModel::rowCount(const QModelIndex &parent) const
{
    Requirement *parentItem = getValidItem(parent);

    return parentItem->childCount();
}

QVariant RequirementsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(index.column() == 0 && role == Qt::DisplayRole)
        return asRequirement(index)->getTitle();
    else
        return QVariant();
}

QModelIndex RequirementsModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    try{
        Requirement *parentItem = getValidItem(parent);
        Requirement *childItem  = parentItem->getChild(row);

        return createIndex(row, column, childItem);
    }
    catch(...){
        return QModelIndex();
    }
}

QModelIndex RequirementsModel::parent(const QModelIndex &index) const
{
    if(!index.isValid())
        return QModelIndex();

    Requirement *childItem = asRequirement(index);
    Requirement *parentItem = childItem->getParent();

    if(parentItem == root)
        return QModelIndex();
    else
        return createIndex(parentItem->getRow(), 0, parentItem);
}

QVariant RequirementsModel::headerData(int section,
                                       Qt::Orientation orientation,
                                       int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        if(section == 0)
            return tr("Requirement");
    }

    return QVariant();
}

bool RequirementsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Requirement *parentItem;

    if(!parent.isValid())
        parentItem = root;
    else
        parentItem = asRequirement(parent);

    if(parentItem->childCount() == 0){
        beginInsertRows(parent, 0, 0 + count - 1);
        parentItem->insertChildren(0, count);
        endInsertRows();
        return true;
    }
    else if(row <= parentItem->childCount()){
        beginInsertRows(parent, row, row + count - 1);
        parentItem->insertChildren(row, count);
        endInsertRows();
        return true;
    }
    else
        return false;
}

bool RequirementsModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    return true;
}

bool RequirementsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    return true;
}

bool RequirementsModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    return true;
}

bool RequirementsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return true;
}

bool RequirementsModel::appendSibling(const QModelIndex &index)
{
    Requirement *item = getValidItem(index);

    if(item == root)
        insertRows(0, 1, createIndex(0,0,root));
    else
        insertRows(index.row(), 1, parent(index));

    return true;
}

bool RequirementsModel::appendChild(const QModelIndex &index)
{
    Requirement *item = getValidItem(index);
    int beforeRow;

    if(item == root){
        beforeRow = root->childCount();
        insertRows(beforeRow, 1, index);
    }
    else{
        beforeRow = asRequirement(index)->childCount();
        insertRows(beforeRow, 1, index);
    }

    return true;
}

Requirement *RequirementsModel::asRequirement(const QModelIndex &index) const
{
    return static_cast<Requirement*>(index.internalPointer());
}

Requirement *RequirementsModel::getValidItem(const QModelIndex &index) const
{
    if(!index.isValid())
        return root;
    else
        return asRequirement(index);
}


