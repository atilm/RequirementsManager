#include "riskassessment.h"

RiskAssessment::RiskAssessment(shared_ptr<FileStateTracker> fileState,
                               RiskModel *initialRisk,
                               RiskModel *finalRisk,
                               shared_ptr<PreventiveActionModel> preventiveActions)
{
    this->fileState = fileState;
    this->initial = initialRisk;
    this->final = finalRisk;
    this->preventiveActions = preventiveActions;
    scenarioText = QObject::tr("new risk assessment");
}

RiskAssessment::~RiskAssessment()
{
    delete initial;
    delete final;
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
    if(s != scenarioText){
        scenarioText = s;
        fileState->setChanged(true);
    }
}

QString RiskAssessment::mitigationStrategy() const
{
    return mitigationStrategyText;
}

void RiskAssessment::setMitigationStrategy(const QString &s)
{
    if(s != mitigationStrategyText){
        mitigationStrategyText = s;
        fileState->setChanged(true);
    }
}

QVariant RiskAssessment::initialRisk(int role) const
{
    return initial->data(initial->getCurrentRisk(), role);
}

QVariant RiskAssessment::finalRisk(int role) const
{
    return final->data(final->getCurrentRisk(), role);
}

RiskModel *RiskAssessment::initialRiskModel() const
{
    return initial;
}

RiskModel *RiskAssessment::finalRiskModel() const
{
    return final;
}

shared_ptr<PreventiveActionModel> RiskAssessment::getPreventiveActions()
{
    return preventiveActions;
}

int RiskAssessment::preventiveActionCount() const
{
    return preventiveActions->rowCount();
}
