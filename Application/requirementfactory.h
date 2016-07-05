#ifndef REQUIREMENTFACTORY_H
#define REQUIREMENTFACTORY_H

#include "uniqueidmanager.h"
#include "requirement.h"
#include "designreference.h"
#include "attributecontainerfactory.h"
#include "linkcontainerfactory.h"
#include "riskassessmentfactory.h"
#include "filestatetracker.h"

class SourceCodeController;

class RequirementFactory
{
public:
    RequirementFactory(shared_ptr<FileStateTracker> fileState,
                       UniqueIDManager *idManager,
                       AttributeContainerFactory *attrContainerFactory,
                       LinkContainerFactory *linkContainerFactory,
                       SourceCodeController *sourceController);
    virtual ~RequirementFactory();

    Requirement* newRequirement(Requirement *parent = 0);
    Requirement* newRequirement(unsigned int proposedID, Requirement *parent = 0);

    DesignReference* newDesignReference(SourceAddress address, Requirement *parent = 0);
    DesignReference* newDesignReference(SourceAddress address, unsigned int proposedID,
                                        Requirement *parent = 0);

private:
    shared_ptr<FileStateTracker> fileState;
    AttributeContainerFactory *attrContainerFactory;
    LinkContainerFactory *linkContainerFactory;
    UniqueIDManager *idManager;
    SourceCodeController *sourceController;
};

#endif // REQUIREMENTFACTORY_H
