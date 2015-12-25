#include "linkcontainer.h"
#include "linkgroup.h"
#include <QDebug>

LinkContainer::LinkContainer(LinkContext *context, QObject *parent)
    : QAbstractItemModel(parent)
{
    this->context = context;
    this->root = new LinkNode();

    initialize();

    connect(context, SIGNAL(newLinkType(int)),
            this, SLOT(handleLinkTypeInserted(int)));
    connect(context, SIGNAL(linkTypeRemoved(int)),
            this, SLOT(handleLinkTypeRemoved(int)));
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
    LinkNode *parentItem = getValidItem(parent);

    return parentItem->childCount();
}

QVariant LinkContainer::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
        return asLinkNode(index)->toString();
    else
        return QVariant();
}

void LinkContainer::handleLinkTypeInserted(int before)
{
    if(before <= root->childCount() && before >= 0){
        beginInsertRows(QModelIndex(), before, before);
        LinkGroup *group = new LinkGroup();
        group->setName(context->typeName(before));
        root->insertChild(group, before);
        endInsertRows();
    }
}

void LinkContainer::handleLinkTypeRemoved(int index)
{
    if(index < root->childCount() && index >= 0){
        beginRemoveRows(QModelIndex(), index, index);
        root->removeChildAt(index);
        endRemoveRows();
    }
}

void LinkContainer::initialize()
{
    for(int i=0;i<context->rowCount();i++){
        LinkGroup *group = new LinkGroup();
        group->setName(context->typeName(i));
        root->insertChild(group,i);
    }
}

LinkNode *LinkContainer::getValidItem(const QModelIndex &index) const
{
    if(!index.isValid())
        return root;
    else
        return asLinkNode(index);
}

LinkNode *LinkContainer::asLinkNode(const QModelIndex &index) const
{
    return static_cast<LinkNode*>(index.internalPointer());
}

QModelIndex LinkContainer::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    try{
        LinkNode *parentItem = getValidItem(parent);
        LinkNode *childItem = parentItem->getChild(row);

        return createIndex(row, column, childItem);
    }
    catch(...){
        return QModelIndex();
    }
}

QModelIndex LinkContainer::parent(const QModelIndex &index) const
{
    if(!index.isValid())
        return QModelIndex();

    LinkNode *childItem = asLinkNode(index);
    LinkNode *parentItem = childItem->getParent();

    if(parentItem == nullptr || parentItem == root){
        return QModelIndex();
    }
    else{
        return createIndex(parentItem->getRow(), 0, parentItem);
    }
}

QVariant LinkContainer::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal
            && section == 0
            && role == Qt::DisplayRole)
        return tr("Links");
    else
        return QVariant();
}
