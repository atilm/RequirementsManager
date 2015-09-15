#include "requirementsmodel.h"
#include <iostream>
using namespace std;

RequirementsModel::RequirementsModel(RequirementFactory *factory,
                                     QObject *parent) :
    QAbstractItemModel(parent)
{
    this->factory = factory;
    root = factory->newRequirement();
    root->appendChild(factory->newRequirement());
}

RequirementsModel::~RequirementsModel()
{
    delete factory;
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

    if(index.column() == 0 && ( role == Qt::DisplayRole || role == Qt::EditRole ) )
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
        for(int i=0;i<count;i++)
            parentItem->insertChild(0, factory->newRequirement());
        endInsertRows();
        return true;
    }
    else if(row <= parentItem->childCount()){
        beginInsertRows(parent, row, row + count - 1);
        for(int i=0;i<count;i++)
            parentItem->insertChild(row, factory->newRequirement());
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

Qt::ItemFlags RequirementsModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;
    else
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool RequirementsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if(role == Qt::EditRole){
        asRequirement(index)->setTitle(value.toString());
        emit dataChanged(index, index);
        return true;
    }
    else
        return false;
}

bool RequirementsModel::appendSibling(const QModelIndex &index)
{
    Requirement *item = getValidItem(index);

    if(item != root)
        insertRows(index.row()+1, 1, parent(index));

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


