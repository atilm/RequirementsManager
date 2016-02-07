#ifndef LINKCONTAINERFACTORY_H
#define LINKCONTAINERFACTORY_H

#include "linkcontext.h"
#include "linkcontainer.h"
#include "uniqueidmanager.h"

class LinkContainerFactory
{
public:
    LinkContainerFactory(LinkContext *context, UniqueIDManager *idManager);
    virtual ~LinkContainerFactory();

    LinkContainer* newContainer();

private:
    LinkContext *context;
    UniqueIDManager *idManager;
};

#endif // LINKCONTAINERFACTORY_H
