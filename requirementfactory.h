#ifndef REQUIREMENTFACTORY_H
#define REQUIREMENTFACTORY_H

#include "uniqueidmanager.h"
#include "requirement.h"
#include "attributecontext.h"

class RequirementFactory
{
public:
    RequirementFactory(UniqueIDManager *idManager, AttributeContext *attributeContext);
    virtual ~RequirementFactory();

    Requirement* newRequirement(Requirement *parent = 0);
    Requirement* newRequirement(unsigned int proposedID, Requirement *parent = 0);

private:
    UniqueIDManager *idManager;
};

#endif // REQUIREMENTFACTORY_H
