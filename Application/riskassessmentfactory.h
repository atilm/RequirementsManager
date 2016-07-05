#ifndef RISKASSESSMENTFACTORY_H
#define RISKASSESSMENTFACTORY_H

#include "riskassessment.h"
#include "riskmodel.h"

#include <memory>
using namespace std;

class RiskAssessmentFactory
{
public:
    RiskAssessmentFactory(shared_ptr<FileStateTracker> fileState);
    virtual ~RiskAssessmentFactory();

    RiskAssessment* newAssessment();

private:
    shared_ptr<FileStateTracker> fileState;
};

#endif // RISKASSESSMENTFACTORY_H
