#ifndef REQUIREMENTFACTORY_H
#define REQUIREMENTFACTORY_H

#include "uniqueidmanager.h"
#include "requirement.h"
#include "attributecontainerfactory.h"
#include "linkcontainerfactory.h"
#include "riskassessmentfactory.h"
#include "filestatetracker.h"

class RequirementFactory
{
public:
    RequirementFactory(FileStateTracker *fileState,
                       UniqueIDManager *idManager,
                       AttributeContainerFactory *attrContainerFactory,
                       LinkContainerFactory *linkContainerFactory);
    virtual ~RequirementFactory();

    Requirement* newRequirement(Requirement *parent = 0);
    Requirement* newRequirement(unsigned int proposedID, Requirement *parent = 0);

private:
    FileStateTracker *fileState;
    AttributeContainerFactory *attrContainerFactory;
    LinkContainerFactory *linkContainerFactory;
    UniqueIDManager *idManager;
};

#endif // REQUIREMENTFACTORY_H
