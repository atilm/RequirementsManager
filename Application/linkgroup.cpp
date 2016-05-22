#include "linkgroup.h"

LinkGroup::LinkGroup()
    : LinkNode()
{

}

LinkToRequirement *LinkGroup::getLink(int i) const
{
    return dynamic_cast<LinkToRequirement*>(getChild(i));
}
