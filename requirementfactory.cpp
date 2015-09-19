#include "requirementfactory.h"

RequirementFactory::RequirementFactory(UniqueIDManager *idManager)
{
    this->idManager = idManager;
}

RequirementFactory::~RequirementFactory()
{
    delete idManager;
}

Requirement *RequirementFactory::newRequirement(Requirement* parent)
{
    Requirement *item = new Requirement(idManager);
    item->setParent(parent);
    return item;
}

Requirement *RequirementFactory::newRequirement(unsigned int proposedID, Requirement *parent)
{
    Requirement *item = new Requirement(idManager, proposedID);
    item->setParent(parent);
    return item;
}
