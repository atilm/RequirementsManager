#ifndef LINKGROUP_H
#define LINKGROUP_H

#include <QVector>

#include "linknode.h"
#include "linktorequirement.h"

class LinkGroup : public LinkNode
{
public:
    LinkGroup();

    LinkToRequirement* getLink(int i) const;

private:
};

#endif // LINKGROUP_H
