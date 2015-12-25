#include "linkgroup.h"

LinkGroup::LinkGroup()
    : LinkNode()
{

}

QString LinkGroup::getName() const
{
    return name;
}

void LinkGroup::setName(const QString &name)
{
    this->name = name;
}

QString LinkGroup::toString() const
{
    return name;
}
