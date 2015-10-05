#include "attributecontainerfactory.h"

AttributeContainerFactory::AttributeContainerFactory(AttributeContext *context)
{
    this->context = context;
}

AttributeContainerFactory::~AttributeContainerFactory()
{

}

AttributeContainer *AttributeContainerFactory::newContainer()
{
    return new AttributeContainer(context);
}
