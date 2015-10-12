#ifndef ATTRIBUTECONTAINERMOCK_H
#define ATTRIBUTECONTAINERMOCK_H

#include "gmock/gmock.h"
#include "attributecontainer.h"

class AttributeContainerMock : public AttributeContainer{
public:
    AttributeContainerMock() : AttributeContainer(nullptr) {}

};


#endif // ATTRIBUTECONTAINERMOCK_H
