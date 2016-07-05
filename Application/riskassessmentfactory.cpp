#include "riskassessmentfactory.h"

RiskAssessmentFactory::RiskAssessmentFactory(shared_ptr<FileStateTracker> fileState)
{
    this->fileState = fileState;
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
                                            new PreventiveActionModel(fileState)));
}
