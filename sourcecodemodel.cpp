#include "sourcecodemodel.h"

SourceCodeModel::SourceCodeModel()
{
    root = new SourceNode();
}

SourceCodeModel::~SourceCodeModel()
{

}

int SourceCodeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

int SourceCodeModel::rowCount(const QModelIndex &parent) const
{
    return getValidItem(parent)->childCount();
}

QVariant SourceCodeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
        return asSourceNode(index)->getName();
    else
        return QVariant();
}

QModelIndex SourceCodeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    try{
        SourceNode *parentItem = getValidItem(parent);
        SourceNode *childItem = parentItem->getChild(row);

        return createIndex(row, column, childItem);
    }
    catch(...){
        return QModelIndex();
    }
}

QModelIndex SourceCodeModel::parent(const QModelIndex &index) const
{
    if(!index.isValid())
        return QModelIndex();

    SourceNode *childItem = asSourceNode(index);
    SourceNode *parentItem = childItem->getParent();

    if(parentItem == nullptr || parentItem == root)
        return QModelIndex();
    else
        return createIndex(parentItem->getRow(), 0, parentItem);
}

QVariant SourceCodeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

Qt::ItemFlags SourceCodeModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex SourceCodeModel::appendClass(SourceNode *node)
{
    int rowIdx = root->childCount();

    beginInsertRows(QModelIndex(), rowIdx, rowIdx);
    root->appendChild(node);
    endInsertRows();

    return index(rowIdx, 0);
}

SourceNode *SourceCodeModel::asSourceNode(const QModelIndex &index) const
{
    return static_cast<SourceNode*>(index.internalPointer());
}

SourceNode *SourceCodeModel::getValidItem(const QModelIndex &index) const
{
    if(!index.isValid())
        return root;
    else
        return asSourceNode(index);
}

