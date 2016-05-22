#include "linktorequirement.h"
#include "requirement.h"

LinkToRequirement::LinkToRequirement(unsigned int id)
    : LinkNode()
{
    linkedID = id;
}

LinkToRequirement::~LinkToRequirement()
{

}

unsigned int LinkToRequirement::getID() const
{
    return linkedID;
}
