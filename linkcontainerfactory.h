#ifndef LINKCONTAINERFACTORY_H
#define LINKCONTAINERFACTORY_H

#include "linkcontext.h"
#include "linkcontainer.h"

class LinkContainerFactory
{
public:
    LinkContainerFactory(LinkContext *context);
    virtual ~LinkContainerFactory();

    LinkContainer* newContainer();

private:
    LinkContext *context;
};

#endif // LINKCONTAINERFACTORY_H
