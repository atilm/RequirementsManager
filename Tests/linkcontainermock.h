#ifndef LINKCONTAINERMOCK
#define LINKCONTAINERMOCK

#include "gmock/gmock.h"
#include "linkcontainer.h"

class LinkContainerMock : public LinkContainer{
public:
    LinkContainerMock() : LinkContainer(nullptr, nullptr, nullptr) {}

};

#endif // LINKCONTAINERMOCK

