#include "linktorequirement.h"

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
    return "link to requirement";
}

