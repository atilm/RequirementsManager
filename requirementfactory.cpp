#include "requirementfactory.h"

RequirementFactory::RequirementFactory(FileStateTracker *fileState,
                                       UniqueIDManager *idManager,
                                       AttributeContainerFactory *attrContainerFactory,
                                       LinkContainerFactory *linkContainerFactory)
{
    this->fileState = fileState;
    this->idManager = idManager;
    this->attrContainerFactory = attrContainerFactory;
    this->linkContainerFactory = linkContainerFactory;
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
