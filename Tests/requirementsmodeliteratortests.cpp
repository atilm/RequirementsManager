#include "gtest/gtest.h"

#include "appsettings.h"
#include "preventiveactionfactory.h"
#include "requirementsmodeliterator.h"
#include "sourcecodecontrollermock.h"
using namespace std;

class ModelIteratorTests : public ::testing::Test{
protected:
    RequirementsModel *model;
    AttributeContext *attributeContext;
    LinkContext *linkContext;
    RequirementToModelMapper *reqToModelMapper;
    SourceCodeControllerMock *sourceCodeController;
    UniqueIDManager *idManager;
    RequirementRefCounter *reqRefCounter;
    AttributeContainerFactory *attrContainerFactory;
    LinkContainerFactory *linkContainerFactory;
    AppSettings *appSettings;

    shared_ptr<FileStateTracker> fileStateTracker;
    shared_ptr<PreventiveActionFactory> preventiveActionFactory;
    shared_ptr<RiskAssessmentFactory> raFactory;

    ModelIteratorTests(){

        fileStateTracker = make_shared<FileStateTracker>();
        attributeContext = new AttributeContext(fileStateTracker);
        linkContext = new LinkContext(fileStateTracker);
        reqToModelMapper = new RequirementToModelMapper(attributeContext);

        sourceCodeController = new SourceCodeControllerMock();

        preventiveActionFactory =
                make_shared<PreventiveActionFactory>(fileStateTracker,
                                                     sourceCodeController);

        raFactory = make_shared<RiskAssessmentFactory>(fileStateTracker,
                                                       preventiveActionFactory);

        idManager = new UniqueIDManager();
        reqRefCounter = new RequirementRefCounter();
        attrContainerFactory = new AttributeContainerFactory(attributeContext);
        linkContainerFactory = new LinkContainerFactory(linkContext, idManager);
        appSettings = new AppSettings();

        RequirementFactory *factory =
                new RequirementFactory(fileStateTracker,
                                       raFactory,
                                       idManager,
                                       reqRefCounter,
                                       attrContainerFactory,
                                       linkContainerFactory,
                                       sourceCodeController,
                                       appSettings);


        model = new RequirementsModel(factory,
                                      fileStateTracker,
                                      attributeContext,
                                      linkContext,
                                      reqToModelMapper);
    }

    virtual ~ModelIteratorTests(){
        delete model;
        delete attributeContext;
        delete linkContext;
        delete reqToModelMapper;
        delete sourceCodeController;
        delete idManager;
        delete reqRefCounter;
        delete attrContainerFactory;
        delete linkContainerFactory;
        delete appSettings;
    }
};

TEST_F(ModelIteratorTests, compile_test){

}
