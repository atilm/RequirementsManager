#include "requirementfactory.h"

RequirementFactory::RequirementFactory(UniqueIDManager *idManager)
{
    this->idManager = idManager;
}

RequirementFactory::~RequirementFactory()
{
    delete idManager;
}

Requirement *RequirementFactory::newRequirement()
{
    return new Requirement(idManager->newUniqueID());
}

Requirement *RequirementFactory::newRequirement(unsigned int proposedID)
{
    if(idManager->hasID(proposedID))
        throw IDCollisionException();
    else{
        idManager->addID(proposedID);
        return new Requirement(proposedID);
    }
}
