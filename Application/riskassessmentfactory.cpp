#include "riskassessmentfactory.h"

RiskAssessmentFactory::RiskAssessmentFactory(FileStateTracker *fileState)
{
    this->fileState = fileState;
}

RiskAssessmentFactory::~RiskAssessmentFactory()
{

}

RiskAssessment *RiskAssessmentFactory::newAssessment()
{
    return new RiskAssessment(fileState,
                              new RiskModel(fileState),
                              new RiskModel(fileState),
                              new PreventiveActionModel(fileState));
}
