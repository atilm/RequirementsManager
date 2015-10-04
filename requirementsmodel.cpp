#include "requirementsmodel.h"
#include <iostream>
using namespace std;

RequirementsModel::RequirementsModel(RequirementFactory *factory, FileStateTracker *fileState, AttributeContext *attributeContext,
                                     QObject *parent) :
    QAbstractItemModel(parent)
{
    this->factory = factory;
    this->fileState = fileState;
    this->attributeContext = attributeContext;
}

RequirementsModel::~RequirementsModel()
{
    delete factory;
}

void RequirementsModel::init()
{
    root = factory->newRequirement();
}

void RequirementsModel::clearModel()
{
    int rows = rowCount();

    for(int r=0;r<rows;r++){
        removeRequirement(index(0, 0));
    }
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

    int column = index.column();

    if(column == 0){
        if( role == Qt::DisplayRole || role == Qt::EditRole )
            return asRequirement(index)->getTitle();
    }
    else if(column <= attributeContext->rowCount()){
        AttributeContext::DataType type = attributeContext->type(column);

        switch(type){
        case AttributeContext::BOOLEAN:
            if(role == Qt::CheckStateRole)
                return asRequirement(index)->getAttribute(column);
            break;
        case AttributeContext::INTEGER:
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return asRequirement(index)->getAttribute(column);
            break;
        case AttributeContext::TEXT:
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return asRequirement(index)->getAttribute(column);
        }
    }

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
        return Qt::ItemIsDropEnabled;
    else
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable |
               Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

bool RequirementsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if(role == Qt::EditRole){
        asRequirement(index)->setTitle(value.toString());
        emit dataChanged(index, index);
        fileState->setChanged(true);
        return true;
    }
    else
        return false;
}

Qt::DropActions RequirementsModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

QModelIndex RequirementsModel::appendSibling(const QModelIndex &index)
{
    if(!index.isValid())
        return appendChild(index);
    else{
        Requirement *parent = getValidItem(index.parent());

        if(index.row() < parent->childCount()){
            beginInsertRows(index.parent(), index.row()+1, index.row()+1);
            Requirement *child = factory->newRequirement();
            parent->insertChild(index.row()+1, child);
            endInsertRows();

            fileState->setChanged(true);
            connect(child->getDescription(), SIGNAL(contentsChanged()),
                    this, SLOT(handleDescriptionChanged()));
            return this->index(index.row()+1, 0, index.parent());
        }
        else
            return QModelIndex();
    }
}

QModelIndex RequirementsModel::appendChild(const QModelIndex &index)
{
    Requirement *item = getValidItem(index);
    Requirement *newItem = factory->newRequirement();

    beginInsertRows(index, item->childCount(), item->childCount());
    item->appendChild(newItem);
    endInsertRows();

    fileState->setChanged(true);
    connect(newItem->getDescription(), SIGNAL(contentsChanged()),
            this, SLOT(handleDescriptionChanged()));
    return this->index(item->childCount()-1, 0, index);
}

QModelIndex RequirementsModel::insertChild(Requirement *newItem, const QModelIndex &index, int beforeRow)
{
    Requirement *item = getValidItem(index);

    beginInsertRows(index, beforeRow, beforeRow);
    item->insertChild(beforeRow, newItem);
    endInsertRows();

    fileState->setChanged(true);
    connect(newItem->getDescription(), SIGNAL(contentsChanged()),
            this, SLOT(handleDescriptionChanged()));
    return this->index(beforeRow-1, 0, index);
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
        fileState->setChanged(true);
        return true;
    }
}

void RequirementsModel::moveRequirement(const QModelIndex &source, const QModelIndex &destination)
{
    QModelIndex sourceParent = parent(source);
    QModelIndex destinationParent = parent(destination);

    if(sourceParent == destinationParent &&
       source.row() == destination.row() - 1)
        return;

    if(destination.row() < 0)
        return;

    Requirement *sourceItem = asRequirement(source);

    //beginMoveRows(sourceParent, source.row(), source.row(), destinationParent, destination.row());

    insertChild(sourceItem, destinationParent, destination.row());

    int removeIndex = source.row();

    // when a copy of source is inserted before source, then the index
    // of source is shifted to its former position + 1:
    if(sourceParent == destinationParent){
        if(source.row() > destination.row()){
            removeIndex += 1;
        }
    }

    Requirement *sourceParentItem = getValidItem(sourceParent);

    beginRemoveRows(sourceParent, removeIndex, removeIndex);
    sourceParentItem->popChild(removeIndex);
    endRemoveRows();

    fileState->setChanged(true);

    //endMoveRows();
}

QTextDocument *RequirementsModel::getDescription(const QModelIndex &index)
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

void RequirementsModel::handleDescriptionChanged()
{
    fileState->setChanged(true);
}


