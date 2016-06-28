#include "sourcenode.h"
#include <stdexcept>
using namespace std;

#include <QDebug>

SourceNode::SourceNode()
{
    parent = nullptr;
}

SourceNode::~SourceNode()
{
    foreach(SourceNode *child, children)
        delete child;
}

void SourceNode::setName(const QString &name)
{
    this->name = name;
}

QString SourceNode::getName() const
{
    return name;
}

void SourceNode::setDescription(const QString &s)
{
    description = s;
}

QString SourceNode::getDescription() const
{
    return description;
}

int SourceNode::childCount() const
{
    return children.count();
}

SourceNode *SourceNode::getChild(int index) const
{
    if(index >= 0 && index < children.count())
        return children[index];
    else
        throw runtime_error("Invalid SourceNode child index");
}

void SourceNode::insertChild(uint index, SourceNode *child)
{
    if(index >= 0 && index <= children.count()){
        child->setParent(this);
        children.insert(index, child);
    }
    else
        throw runtime_error("Invalid SourceNode child insertion index");
}

void SourceNode::appendChild(SourceNode *child)
{
    child->setParent(this);
    children.append(child);
}

void SourceNode::setParent(SourceNode *parent)
{
    this->parent = parent;
}

SourceNode *SourceNode::getParent() const
{
    return parent;
}

int SourceNode::getRow()
{
    return parent->indexOf(this);
}

int SourceNode::indexOf(SourceNode *child) const
{
    return children.indexOf(child);
}

