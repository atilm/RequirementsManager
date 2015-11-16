#ifndef RISKASSESSMENT_H
#define RISKASSESSMENT_H

#include <QString>
#include "preventiveactionmodel.h"
#include "riskmodel.h"

class RiskAssessment
{
public:

    RiskAssessment(RiskModel *initialRisk,
                   RiskModel *finalRisk,
                   PreventiveActionModel *preventiveActions);
    virtual ~RiskAssessment();

    virtual QString shortScenario() const;
    virtual QString scenario() const;
    virtual void setScenario(const QString &s);
    virtual QVariant initialRisk(int role) const;
    virtual QVariant finalRisk(int role) const;
    virtual RiskModel* initialRiskModel();
    virtual RiskModel* finalRiskModel();

    virtual PreventiveActionModel* getPreventiveActions();

private:
    RiskModel *initial;
    RiskModel *final;
    QString scenarioText;
    PreventiveActionModel *preventiveActions;
};

#endif // RISKASSESSMENT_H
