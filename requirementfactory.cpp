#include "requirementfactory.h"

RequirementFactory::RequirementFactory(UniqueIDManager *idManager,
                                       AttributeContainerFactory *attrContainerFactory)
{
    this->idManager = idManager;
    this->attrContainerFactory = attrContainerFactory;
}

RequirementFactory::~RequirementFactory()
{
    delete idManager;
}

Requirement *RequirementFactory::newRequirement(Requirement* parent)
{
    Requirement *item = new Requirement(idManager,
                                        attrContainerFactory->newContainer());
    item->setParent(parent);
    return item;
}

Requirement *RequirementFactory::newRequirement(unsigned int proposedID, Requirement *parent)
{
    Requirement *item = new Requirement(idManager,
                                        attrContainerFactory->newContainer());
    item->setParent(parent);
    return item;
}
