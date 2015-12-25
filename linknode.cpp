#include "linknode.h"

#include <stdexcept>
using namespace std;

LinkNode::LinkNode()
{
    this->parent = nullptr;
}

QString LinkNode::toString() const
{
    return QString();
}

LinkNode *LinkNode::getChild(int index)
{
    if(isValidIndex(index))
        return children[index];
    else
        throw runtime_error("LinkNode: Invalid index.");
}

LinkNode *LinkNode::getParent()
{
    return parent;
}

int LinkNode::childCount() const
{
    return children.count();
}

void LinkNode::insertChild(LinkNode *node, int before)
{
    if(before >= 0 && before <= children.count())
        children.insert(before, node);
}

void LinkNode::removeChildAt(int index)
{
    if(isValidIndex(index))
        children.remove(index);
}

void LinkNode::setParent(LinkNode *parent)
{
    this->parent = parent;
}

int LinkNode::getRow()
{
    if(parent)
        return parent->indexOf(this);
    else
        return 0;
}

int LinkNode::indexOf(const LinkNode *node) const
{
    for(int i=0;i<childCount();i++){
        if(node == children.at(i))
            return i;
    }
    return -1;
}

bool LinkNode::isValidIndex(int index) const
{
    if(index < children.count() && index >= 0)
        return true;
    else
        return false;
}

