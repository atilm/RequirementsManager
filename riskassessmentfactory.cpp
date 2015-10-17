#include "riskassessmentfactory.h"

RiskAssessmentFactory::RiskAssessmentFactory()
{
}

RiskAssessmentFactory::~RiskAssessmentFactory()
{

}

RiskAssessment *RiskAssessmentFactory::newAssessment()
{
    return new RiskAssessment(new PreventiveActionModel());
}
