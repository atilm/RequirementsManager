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

    if(role == Qt::DisplayRole){
        if(asLinkGroup(index))
            return context->typeName(index.row());
        else
            return asLinkNode(index)->toString();
    }
    else
        return QVariant();
}

void LinkContainer::handleLinkTypeInserted(int before)
{
    if(before <= root->childCount() && before >= 0){
        beginInsertRows(QModelIndex(), before, before);
        root->insertChild(new LinkGroup(), before);
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

void LinkContainer::addLink(const QModelIndex &index, LinkToRequirement *link)
{
    if(!index.isValid())
        return;

    QModelIndex groupIndex = index;
    LinkGroup *group = asLinkGroup(groupIndex);
    if(!group){
        groupIndex = index.parent();
        group = asLinkGroup(groupIndex);
    }

    int before = group->childCount();
    beginInsertRows(groupIndex, before, before);
    group->insertChild(link, group->childCount());
    endInsertRows();
}

void LinkContainer::initialize()
{
    for(int i=0;i<context->rowCount();i++)
        root->insertChild(new LinkGroup(),i);
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

LinkGroup *LinkContainer::asLinkGroup(const QModelIndex &index) const
{
    // call to asLinkNode() because dynamic_cast only takes
    // pointers to classes and index.internalPointer() returns
    // a void*
    return dynamic_cast<LinkGroup*>(asLinkNode(index));
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
