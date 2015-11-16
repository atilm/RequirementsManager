#include "riskassessment.h"

RiskAssessment::RiskAssessment(RiskModel *initialRisk,
                               RiskModel *finalRisk,
                               PreventiveActionModel *preventiveActions)
{
    this->initial = initialRisk;
    this->final = finalRisk;
    this->preventiveActions = preventiveActions;
}

RiskAssessment::~RiskAssessment()
{
    delete initial;
    delete final;
    delete preventiveActions;
}

QString RiskAssessment::shortScenario() const
{
    int lineEnd = scenarioText.indexOf("\n");

    if(lineEnd < 0)
        return scenarioText;
    else
        return scenarioText.mid(0, lineEnd);
}

QString RiskAssessment::scenario() const
{
    return scenarioText;
}

void RiskAssessment::setScenario(const QString &s)
{
    scenarioText = s;
}

QVariant RiskAssessment::initialRisk(int role) const
{
    return initial->data(initial->getCurrentRisk(), role);
}

QVariant RiskAssessment::finalRisk(int role) const
{
    return final->data(final->getCurrentRisk(), role);
}

RiskModel *RiskAssessment::initialRiskModel()
{
    return initial;
}

RiskModel *RiskAssessment::finalRiskModel()
{
    return final;
}

PreventiveActionModel *RiskAssessment::getPreventiveActions()
{
    return preventiveActions;
}
