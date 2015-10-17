#ifndef REQUIREMENTFACTORY_H
#define REQUIREMENTFACTORY_H

#include "uniqueidmanager.h"
#include "requirement.h"
#include "attributecontainerfactory.h"
#include "riskassessmentfactory.h"

class RequirementFactory
{
public:
    RequirementFactory(UniqueIDManager *idManager,
                       AttributeContainerFactory *attrContainerFactory);
    virtual ~RequirementFactory();

    Requirement* newRequirement(Requirement *parent = 0);
    Requirement* newRequirement(unsigned int proposedID, Requirement *parent = 0);

private:
    AttributeContainerFactory *attrContainerFactory;
    UniqueIDManager *idManager;
};

#endif // REQUIREMENTFACTORY_H
