#include "linktorequirement.h"
#include "requirement.h"

LinkToRequirement::LinkToRequirement(Requirement *link)
    : LinkNode()
{
    linkedRequirement = link;
}

LinkToRequirement::~LinkToRequirement()
{

}

QString LinkToRequirement::toString() const
{
    if(linkedRequirement)
        return linkedRequirement->getNumberedTitle();
}

