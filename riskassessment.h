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
    virtual QString scenario() const;
    virtual void setScenario(const QString &s);
    virtual QString initialRisk() const;
    virtual QString finalRisk() const;

    virtual PreventiveActionModel* getPreventiveActions();

private:
    QString scenarioText;
    PreventiveActionModel *preventiveActions;
};

#endif // RISKASSESSMENT_H
