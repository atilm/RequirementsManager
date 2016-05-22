#include "linkcontainerfactory.h"

LinkContainerFactory::LinkContainerFactory(LinkContext *context, UniqueIDManager *idManager)
{
    this->context = context;
    this->idManager = idManager;
}

LinkContainerFactory::~LinkContainerFactory()
{
}

LinkContainer *LinkContainerFactory::newContainer()
{
    return new LinkContainer(context, idManager);
}
