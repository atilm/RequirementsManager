#ifndef REQUIREMENTREFERENCE_H
#define REQUIREMENTREFERENCE_H

#include "requirement.h"

class RequirementReference : public Requirement
{
public:
    RequirementReference(Requirement *source,
                         UniqueIDManager *idManager,
                         shared_ptr<RiskAssessmentModel> riskAssessment,
                         AppSettings *settings);
    virtual ~RequirementReference();

    virtual bool isReference();
    virtual QString getNumberedTitle() const;
    virtual QTextDocument* getDescription();

protected:
    Requirement *source;
    shared_ptr<QTextDocument> refDescription;
};

#endif // REQUIREMENTREFERENCE_H
