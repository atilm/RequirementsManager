#include "requirementsmodel.h"
#include <iostream>
using namespace std;

RequirementsModel::RequirementsModel(RequirementFactory *factory,
                                     QObject *parent) :
    QAbstractItemModel(parent)
{
    this->factory = factory;
    root = factory->newRequirement();
    //root->appendChild(factory->newRequirement());
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

    if(parentItem == NULL || parentItem == root)
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
    if(!index.isValid())
        return appendChild(index);
    else{
        Requirement *parent = getValidItem(index.parent());

        if(index.row() < parent->childCount()){
            beginInsertRows(index.parent(), index.row()+1, index.row()+1);
            parent->insertChild(index.row()+1, factory->newRequirement());
            endInsertRows();
            return true;
        }
        else
            return false;
    }
}

bool RequirementsModel::appendChild(const QModelIndex &index)
{
    Requirement *item = getValidItem(index);

    beginInsertRows(index, item->childCount(), item->childCount());
    item->appendChild(factory->newRequirement());
    endInsertRows();

    return true;
}

bool RequirementsModel::removeRequirement(const QModelIndex &index)
{
    if(!index.isValid())
        return false;
    else{
        Requirement *parent = getValidItem(index.parent());
        beginRemoveRows(index.parent(), index.row(), index.row());
        parent->removeChild(index.row());
        endRemoveRows();
        return true;
    }
}

void RequirementsModel::setDescription(const QModelIndex &index, const QString &description)
{
    if(!index.isValid())
        throw InvalidModelIndexException();

    Requirement *item = asRequirement(index);
    return item->setDescription(description);
}

QString RequirementsModel::getDescription(const QModelIndex &index)
{
    if(!index.isValid())
        throw InvalidModelIndexException();

    Requirement *item = asRequirement(index);
    return item->getDescription();
}

uint RequirementsModel::getID(const QModelIndex &index)
{
    if(!index.isValid())
        throw InvalidModelIndexException();

    return asRequirement(index)->getID();
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


