#include "linkcontainer.h"
#include "linkgroup.h"
#include "requirement.h"
#include <QDebug>

LinkContainer::LinkContainer(LinkContext *context,
                             UniqueIDManager *idManager,
                             QObject *parent)
    : QAbstractItemModel(parent)
{
    this->owner = nullptr;
    this->context = context;
    this->idManager = idManager;
    this->root = new LinkNode();

    initialize();

    connectSignals();
}

LinkContainer::~LinkContainer()
{
    delete root;
}

void LinkContainer::setOwner(Requirement *r)
{
    owner = r;
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
        else{
            unsigned int requirementID = asLinkToRequirement(index)->getID();
            return requirementIDToString(requirementID);
        }
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

void LinkContainer::handleRequirementRemoved(unsigned int id)
{
    for(int g=0;g < root->childCount();g++){
        LinkNode *group = root->getChild(g);
        for(int i=0;i < group->childCount();i++){
            LinkToRequirement *link = static_cast<LinkToRequirement*>(group->getChild(i));
            if(link->getID() == id)
                group->removeChildAt(i);
        }
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

void LinkContainer::addLink(int groupIdx, unsigned int requirementID)
{
    QModelIndex groupModelIdx = index(groupIdx, 0, QModelIndex());

    addLink(groupModelIdx, new LinkToRequirement(requirementID));
}

void LinkContainer::removeLink(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    if(asLinkGroup(index))
        return;

    LinkGroup *group = asLinkGroup(index.parent());
    beginRemoveRows(index.parent(),index.row(),index.row());
    group->removeChildAt(index.row());
    endRemoveRows();
}

void LinkContainer::initialize()
{
    if(!context)
        return;

    for(int i=0;i<context->rowCount();i++)
        root->insertChild(new LinkGroup(),i);
}

void LinkContainer::connectSignals()
{
    if(context){
        connect(context, SIGNAL(newLinkType(int)),
                this, SLOT(handleLinkTypeInserted(int)));
        connect(context, SIGNAL(linkTypeRemoved(int)),
                this, SLOT(handleLinkTypeRemoved(int)));
        connect(idManager, SIGNAL(idRemoved(unsigned int)),
                this, SLOT(handleRequirementRemoved(unsigned int)));
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

LinkGroup *LinkContainer::asLinkGroup(const QModelIndex &index) const
{
    // call to asLinkNode() because dynamic_cast only takes
    // pointers to classes and index.internalPointer() returns
    // a void*
    return dynamic_cast<LinkGroup*>(asLinkNode(index));
}

LinkToRequirement *LinkContainer::asLinkToRequirement(const QModelIndex &index) const
{
    // call to asLinkNode() because dynamic_cast only takes
    // pointers to classes and index.internalPointer() returns
    // a void*
    return dynamic_cast<LinkToRequirement*>(asLinkNode(index));
}

QString LinkContainer::requirementIDToString(unsigned int id) const
{
    try{
        Requirement *r = idManager->getRequirement(id);
        return r->getNumberedTitle();
    }
    catch(const IDUnknownException &e){
        return QString("unresolved id(%1)").arg(id);
    }
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
        return tr("Links to %1").arg(owner->getNumberedTitle());
    else
        return QVariant();
}

LinkGroup *LinkContainer::getLinkGroup(int row) const
{
    return asLinkGroup(index(row, 0, QModelIndex()));
}
