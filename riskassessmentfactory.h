#ifndef RISKASSESSMENTFACTORY_H
#define RISKASSESSMENTFACTORY_H

#include "riskassessment.h"
#include "riskmodel.h"

class RiskAssessmentFactory
{
public:
    RiskAssessmentFactory(FileStateTracker *fileState);
    virtual ~RiskAssessmentFactory();

    RiskAssessment* newAssessment();

private:
    FileStateTracker *fileState;
};

#endif // RISKASSESSMENTFACTORY_H
