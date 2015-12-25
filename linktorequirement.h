#ifndef LINKTOREQUIREMENT_H
#define LINKTOREQUIREMENT_H

#include <QString>
#include "linknode.h"

class Requirement;

class LinkToRequirement : public LinkNode
{
public:
    LinkToRequirement(Requirement *link);
    virtual ~LinkToRequirement();

    virtual QString toString() const;

private:
    Requirement *linkedRequirement;
};

#endif // LINKTOREQUIREMENT_H
