#ifndef RISKASSESSMENT_H
#define RISKASSESSMENT_H

#include <QString>
#include "preventiveactionmodel.h"
#include "riskmodel.h"
#include "filestatetracker.h"

class RiskAssessment
{
public:

    RiskAssessment(shared_ptr<FileStateTracker> fileState,
                   RiskModel *initialRisk,
                   RiskModel *finalRisk,
                   PreventiveActionModel *preventiveActions);
    virtual ~RiskAssessment();

    virtual QString shortScenario() const;
    virtual QString scenario() const;
    virtual void setScenario(const QString &s);
    virtual QString mitigationStrategy() const;
    virtual void setMitigationStrategy(const QString &s);
    virtual QVariant initialRisk(int role) const;
    virtual QVariant finalRisk(int role) const;
    virtual RiskModel* initialRiskModel() const;
    virtual RiskModel* finalRiskModel() const;

    virtual PreventiveActionModel* getPreventiveActions();
    virtual int preventiveActionCount() const;

private:
    shared_ptr<FileStateTracker> fileState;
    RiskModel *initial;
    RiskModel *final;
    QString scenarioText;
    QString mitigationStrategyText;
    PreventiveActionModel *preventiveActions;
};

#endif // RISKASSESSMENT_H
