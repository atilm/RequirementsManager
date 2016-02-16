#include "classnode.h"

ClassNode::ClassNode()
{

}

ClassNode::~ClassNode()
{

}

void ClassNode::setName(const QString &name)
{
    this->name = name;
}

QString ClassNode::getName() const
{
    return name;
}

