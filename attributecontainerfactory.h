#ifndef ATTRIBUTECONTAINERFACTORY_H
#define ATTRIBUTECONTAINERFACTORY_H

#include "attributecontainer.h"
#include "attributecontext.h"

class AttributeContainerFactory
{
public:
    AttributeContainerFactory(AttributeContext *context);
    virtual ~AttributeContainerFactory();

    AttributeContainer* newContainer();

private:
    AttributeContext *context;
};

#endif // ATTRIBUTECONTAINERFACTORY_H
