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
    return QString("scenario");
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
