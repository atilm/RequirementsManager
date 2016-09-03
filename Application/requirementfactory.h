#ifndef REQUIREMENTFACTORY_H
#define REQUIREMENTFACTORY_H

#include "appsettings.h"
#include "attributecontainerfactory.h"
#include "uniqueidmanager.h"
#include "requirement.h"
#include "designreference.h"
#include "linkcontainerfactory.h"
#include "riskassessmentfactory.h"
#include "filestatetracker.h"

class SourceCodeController;

class RequirementFactory
{
public:
    RequirementFactory(shared_ptr<FileStateTracker> fileState,
                       shared_ptr<RiskAssessmentFactory> raFactory,
                       UniqueIDManager *idManager,
                       AttributeContainerFactory *attrContainerFactory,
                       LinkContainerFactory *linkContainerFactory,
                       SourceCodeController *sourceController,
                       AppSettings *settings);
    virtual ~RequirementFactory();

    Requirement* newRequirement(Requirement *parent = 0);
    Requirement* newRequirement(unsigned int proposedID, Requirement *parent = 0);

    DesignReference* newDesignReference(SourceAddress address, Requirement *parent = 0);
    DesignReference* newDesignReference(SourceAddress address, unsigned int proposedID,
                                        Requirement *parent = 0);

private:
    shared_ptr<FileStateTracker> fileState;
    shared_ptr<RiskAssessmentFactory> raFactory;
    AttributeContainerFactory *attrContainerFactory;
    LinkContainerFactory *linkContainerFactory;
    UniqueIDManager *idManager;
    SourceCodeController *sourceController;
    AppSettings *settings;
};

#endif // REQUIREMENTFACTORY_H
