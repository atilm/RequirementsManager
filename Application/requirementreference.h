#ifndef REQUIREMENTREFERENCE_H
#define REQUIREMENTREFERENCE_H

#include "requirement.h"

class RequirementReference : public Requirement
{
public:
    RequirementReference(uint targetID,
                         Type type,
                         UniqueIDManager *idManager,
                         RequirementRefCounter *refCounter,
                         shared_ptr<RiskAssessmentModel> riskAssessment,
                         AttributeContainer *attributes,
                         LinkContainer *links,
                         AppSettings *settings);

    RequirementReference(uint targetID,
                         UniqueIDManager *idManager,
                         RequirementRefCounter *refCounter,
                         shared_ptr<RiskAssessmentModel> riskAssessment,
                         AttributeContainer *attributes,
                         LinkContainer *links,
                         AppSettings *settings,
                         uint proposedID);

    virtual ~RequirementReference();

    virtual bool isReference() const;
    virtual QString getTitle() const;
    virtual QString getNumberedTitle() const;
    virtual QTextDocument* getDescription();

    virtual void setTargetID(uint id);
    virtual uint getTargetID() const;

protected:
    uint targetID;
    QTextDocument *refDescription;

    Requirement *getSource() const;
    void initialize(uint targetID, Type type);
};

#endif // REQUIREMENTREFERENCE_H
