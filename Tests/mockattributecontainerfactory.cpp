#include "mockattributecontainerfactory.h"

MockAttributeContainerFactory::MockAttributeContainerFactory() :
    AttributeContainerFactory(nullptr)
{
}

AttributeContainer *MockAttributeContainerFactory::newContainer()
{
    return new AttributeContainerMock();
}
