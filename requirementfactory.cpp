#include "requirementfactory.h"

RequirementFactory::RequirementFactory(UniqueIDManager *idManager,
                                       AttributeContainerFactory *attrContainerFactory)
{
    this->idManager = idManager;
    this->attrContainerFactory = attrContainerFactory;
}

RequirementFactory::~RequirementFactory()
{
    delete idManager;
}

Requirement *RequirementFactory::newRequirement(Requirement* parent)
{
    RiskAssessmentModel *raModel = new RiskAssessmentModel(new RiskAssessmentFactory());

    Requirement *item = new Requirement(idManager,
                                        raModel,
                                        attrContainerFactory->newContainer());
    item->setParent(parent);
    return item;
}

Requirement *RequirementFactory::newRequirement(unsigned int proposedID, Requirement *parent)
{
    RiskAssessmentModel *raModel = new RiskAssessmentModel(new RiskAssessmentFactory());

    Requirement *item = new Requirement(idManager,
                                        raModel,
                                        attrContainerFactory->newContainer(),
                                        proposedID);
    item->setParent(parent);
    return item;
}
