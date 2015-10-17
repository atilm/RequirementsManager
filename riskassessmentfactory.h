#ifndef RISKASSESSMENTFACTORY_H
#define RISKASSESSMENTFACTORY_H

#include "riskassessment.h"

class RiskAssessmentFactory
{
public:
    RiskAssessmentFactory();
    virtual ~RiskAssessmentFactory();

    RiskAssessment* newAssessment();
};

#endif // RISKASSESSMENTFACTORY_H
