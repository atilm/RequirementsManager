#ifndef RISKASSESSMENTFACTORY_H
#define RISKASSESSMENTFACTORY_H

#include "riskassessment.h"
#include "riskmodel.h"

#include <memory>
using namespace std;

class PreventiveActionFactory;

class RiskAssessmentFactory
{
public:
    RiskAssessmentFactory(shared_ptr<FileStateTracker> fileState,
                          shared_ptr<PreventiveActionFactory> actionFactory);
    virtual ~RiskAssessmentFactory();

    shared_ptr<RiskAssessment>  newAssessment();

private:
    shared_ptr<FileStateTracker> fileState;
    shared_ptr<PreventiveActionFactory> actionFactory;
};

#endif // RISKASSESSMENTFACTORY_H
