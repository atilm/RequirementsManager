#include "riskassessmentfactory.h"

RiskAssessmentFactory::RiskAssessmentFactory(shared_ptr<FileStateTracker> fileState,
                                             shared_ptr<PreventiveActionFactory> actionFactory)
{
    this->fileState = fileState;
    this->actionFactory = actionFactory;
}

RiskAssessmentFactory::~RiskAssessmentFactory()
{

}

shared_ptr<RiskAssessment> RiskAssessmentFactory::newAssessment()
{
    return shared_ptr<RiskAssessment>(
                make_shared<RiskAssessment>(fileState,
                                            new RiskModel(fileState),
                                            new RiskModel(fileState),
                                            make_shared<PreventiveActionModel>(fileState,
                                                                               actionFactory)));
}
