#ifndef RISKASSESSMENTFACTORY_H
#define RISKASSESSMENTFACTORY_H

#include "riskassessment.h"
#include "riskmodel.h"

class RiskAssessmentFactory
{
public:
    RiskAssessmentFactory();
    virtual ~RiskAssessmentFactory();

    RiskAssessment* newAssessment();
};

#endif // RISKASSESSMENTFACTORY_H
