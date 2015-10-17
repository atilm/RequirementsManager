#ifndef RISKASSESSMENT_H
#define RISKASSESSMENT_H

#include <QString>

class RiskAssessment
{
public:

    RiskAssessment();
    virtual ~RiskAssessment();

    QString shortScenario() const;
    QString initialRisk() const;
    QString finalRisk() const;

private:

};

#endif // RISKASSESSMENT_H
