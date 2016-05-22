#ifndef LINKTOREQUIREMENT_H
#define LINKTOREQUIREMENT_H

#include <QString>
#include "linknode.h"

class Requirement;

class LinkToRequirement : public LinkNode
{
public:
    LinkToRequirement(unsigned int id);
    virtual ~LinkToRequirement();

    virtual unsigned int getID() const;

private:
    unsigned int linkedID;
};

#endif // LINKTOREQUIREMENT_H
