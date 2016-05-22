#include "requirementfactory.h"
#include "sourcecodecontroller.h"

RequirementFactory::RequirementFactory(FileStateTracker *fileState,
                                       UniqueIDManager *idManager,
                                       AttributeContainerFactory *attrContainerFactory,
                                       LinkContainerFactory *linkContainerFactory,
                                       SourceCodeController *sourceController)
{
    this->fileState = fileState;
    this->idManager = idManager;
    this->attrContainerFactory = attrContainerFactory;
    this->linkContainerFactory = linkContainerFactory;
    this->sourceController = sourceController;
    this->sourceController->injectRequirementsFactory(this);
}

RequirementFactory::~RequirementFactory()
{
    delete idManager;
}

Requirement *RequirementFactory::newRequirement(Requirement* parent)
{
    RiskAssessmentModel *raModel = new RiskAssessmentModel(fileState, new RiskAssessmentFactory(fileState));

    Requirement *item = new Requirement(idManager,
                                        raModel,
                                        attrContainerFactory->newContainer(),
                                        linkContainerFactory->newContainer());
    item->setParent(parent);
    return item;
}

Requirement *RequirementFactory::newRequirement(unsigned int proposedID, Requirement *parent)
{
    RiskAssessmentModel *raModel = new RiskAssessmentModel(fileState, new RiskAssessmentFactory(fileState));

    Requirement *item = new Requirement(idManager,
                                        raModel,
                                        attrContainerFactory->newContainer(),
                                        linkContainerFactory->newContainer(),
                                        proposedID);
    item->setParent(parent);
    return item;
}

DesignReference *RequirementFactory::newDesignReference(SourceAddress address,
                                                        Requirement *parent)
{
    RiskAssessmentModel *raModel = new RiskAssessmentModel(fileState, new RiskAssessmentFactory(fileState));

    DesignReference *item = new DesignReference(address, sourceController,
                                                idManager, raModel,
                                                attrContainerFactory->newContainer(),
                                                linkContainerFactory->newContainer());
    item->setParent(parent);
    return item;
}

DesignReference *RequirementFactory::newDesignReference(SourceAddress address, unsigned int proposedID, Requirement *parent)
{
    RiskAssessmentModel *raModel = new RiskAssessmentModel(fileState, new RiskAssessmentFactory(fileState));

    DesignReference *item = new DesignReference(address, sourceController,
                                                idManager, raModel,
                                                attrContainerFactory->newContainer(),
                                                linkContainerFactory->newContainer(),
                                                proposedID);
    item->setParent(parent);
    return item;
}
