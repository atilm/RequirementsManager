#include "requirementfactory.h"
#include "requirementreference.h"
#include "sourcecodecontroller.h"

RequirementFactory::RequirementFactory(shared_ptr<FileStateTracker> fileState,
                                       shared_ptr<RiskAssessmentFactory> raFactory,
                                       UniqueIDManager *idManager,
                                       RequirementRefCounter *refCounter,
                                       AttributeContainerFactory *attrContainerFactory,
                                       LinkContainerFactory *linkContainerFactory,
                                       SourceCodeController *sourceController,
                                       AppSettings *settings)
{
    this->fileState = fileState;
    this->raFactory = raFactory;
    this->idManager = idManager;
    this->refCounter = refCounter;
    this->attrContainerFactory = attrContainerFactory;
    this->linkContainerFactory = linkContainerFactory;
    this->sourceController = sourceController;
    this->sourceController->injectRequirementsFactory(this);
    this->settings = settings;
}

RequirementFactory::~RequirementFactory()
{
    delete idManager;
    delete refCounter;
}

void RequirementFactory::resetManagers()
{
    refCounter->reset();
    idManager->reset();
}

Requirement *RequirementFactory::newRequirement(Requirement* parent)
{
    shared_ptr<RiskAssessmentModel> raModel(make_shared<RiskAssessmentModel>(fileState, raFactory));

    Requirement *item = new Requirement(idManager,
                                        refCounter,
                                        raModel,
                                        attrContainerFactory->newContainer(),
                                        linkContainerFactory->newContainer(),
                                        settings);
    item->setParent(parent);
    return item;
}

Requirement *RequirementFactory::newRequirement(unsigned int proposedID, Requirement *parent)
{
    shared_ptr<RiskAssessmentModel> raModel(make_shared<RiskAssessmentModel>(fileState, raFactory));

    Requirement *item = new Requirement(idManager,
                                        refCounter,
                                        raModel,
                                        attrContainerFactory->newContainer(),
                                        linkContainerFactory->newContainer(),
                                        settings,
                                        proposedID);
    item->setParent(parent);
    return item;
}

DesignReference *RequirementFactory::newDesignReference(SourceAddress address,
                                                        Requirement *parent)
{
    shared_ptr<RiskAssessmentModel> raModel(make_shared<RiskAssessmentModel>(fileState, raFactory));

    DesignReference *item = new DesignReference(address, sourceController,
                                                idManager,
                                                refCounter,
                                                raModel,
                                                attrContainerFactory->newContainer(),
                                                linkContainerFactory->newContainer(),
                                                settings);
    item->setParent(parent);
    return item;
}

DesignReference *RequirementFactory::newDesignReference(SourceAddress address, unsigned int proposedID,
                                                        Requirement *parent)
{
    shared_ptr<RiskAssessmentModel> raModel(make_shared<RiskAssessmentModel>(fileState, raFactory));

    DesignReference *item = new DesignReference(address, sourceController,
                                                idManager,
                                                refCounter,
                                                raModel,
                                                attrContainerFactory->newContainer(),
                                                linkContainerFactory->newContainer(),
                                                settings,
                                                proposedID);
    item->setParent(parent);
    return item;
}

RequirementReference *RequirementFactory::newRequirementReference(Requirement *source,
                                                                  Requirement *parent)
{
    shared_ptr<RiskAssessmentModel> raModel = make_shared<RiskAssessmentModel>(fileState, raFactory);

    RequirementReference *item = new RequirementReference(source->getID(),
                                                          source->getType(),
                                                          idManager,
                                                          refCounter,
                                                          raModel,
                                                          attrContainerFactory->newContainer(),
                                                          linkContainerFactory->newContainer(),
                                                          settings);

    item->setParent(parent);
    return item;
}

RequirementReference *RequirementFactory::newRequirementReference(uint targetID,
                                                                  uint proposedID,
                                                                  Requirement *parent)
{
    shared_ptr<RiskAssessmentModel> raModel(make_shared<RiskAssessmentModel>(fileState, raFactory));

    RequirementReference *item = new RequirementReference(targetID,
                                                          idManager,
                                                          refCounter,
                                                          raModel,
                                                          attrContainerFactory->newContainer(),
                                                          linkContainerFactory->newContainer(),
                                                          settings,
                                                          proposedID);

    item->setParent(parent);
    return item;
}
