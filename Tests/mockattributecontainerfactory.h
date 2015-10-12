#ifndef MOCKATTRIBUTECONTAINERFACTORY_H
#define MOCKATTRIBUTECONTAINERFACTORY_H

#include "attributecontainerfactory.h"
#include "attributecontainermock.h"

class MockAttributeContainerFactory : public AttributeContainerFactory
{
public:
    MockAttributeContainerFactory();

    AttributeContainer* newContainer();
};

#endif // MOCKATTRIBUTECONTAINERFACTORY_H
