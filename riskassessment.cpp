#include "riskassessment.h"

RiskAssessment::RiskAssessment()
{
}

RiskAssessment::~RiskAssessment()
{

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
