#ifndef REQUIREMENTFACTORY_H
#define REQUIREMENTFACTORY_H

#include "uniqueidmanager.h"
#include "requirement.h"
#include "attributecontainerfactory.h"
#include "riskassessmentfactory.h"
#include "filestatetracker.h"

class RequirementFactory
{
public:
    RequirementFactory(FileStateTracker *fileState,
                       UniqueIDManager *idManager,
                       AttributeContainerFactory *attrContainerFactory);
    virtual ~RequirementFactory();

    Requirement* newRequirement(Requirement *parent = 0);
    Requirement* newRequirement(unsigned int proposedID, Requirement *parent = 0);

private:
    FileStateTracker *fileState;
    AttributeContainerFactory *attrContainerFactory;
    UniqueIDManager *idManager;
};

#endif // REQUIREMENTFACTORY_H
