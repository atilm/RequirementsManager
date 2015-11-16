#include "riskassessmentfactory.h"

RiskAssessmentFactory::RiskAssessmentFactory()
{
}

RiskAssessmentFactory::~RiskAssessmentFactory()
{

}

RiskAssessment *RiskAssessmentFactory::newAssessment()
{
    return new RiskAssessment(new RiskModel(),
                              new RiskModel(),
                              new PreventiveActionModel());
}
