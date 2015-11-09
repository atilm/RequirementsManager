#include "riskassessment.h"

RiskAssessment::RiskAssessment(PreventiveActionModel *preventiveActions)
{
    this->preventiveActions = preventiveActions;
}

RiskAssessment::~RiskAssessment()
{
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

QString RiskAssessment::initialRisk() const
{
    return QString("Unacceptable");
}

QString RiskAssessment::finalRisk() const
{
    return QString("Reasonable");
}

PreventiveActionModel *RiskAssessment::getPreventiveActions()
{
    return preventiveActions;
}
