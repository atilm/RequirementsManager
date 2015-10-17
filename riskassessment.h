#ifndef RISKASSESSMENT_H
#define RISKASSESSMENT_H

#include <QString>
#include "preventiveactionmodel.h"

class RiskAssessment
{
public:

    RiskAssessment(PreventiveActionModel *preventiveActions);
    virtual ~RiskAssessment();

    virtual QString shortScenario() const;
    virtual QString initialRisk() const;
    virtual QString finalRisk() const;

    virtual PreventiveActionModel* getPreventiveActions();

private:
    PreventiveActionModel *preventiveActions;
};

#endif // RISKASSESSMENT_H
