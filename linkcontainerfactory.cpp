#include "linkcontainerfactory.h"

LinkContainerFactory::LinkContainerFactory(LinkContext *context)
{
    this->context = context;
}

LinkContainerFactory::~LinkContainerFactory()
{
}

LinkContainer *LinkContainerFactory::newContainer()
{
    return new LinkContainer(context);
}
