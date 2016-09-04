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

    RequirementReference(uint targetID,
                         UniqueIDManager *idManager,
                         shared_ptr<RiskAssessmentModel> riskAssessment, AttributeContainer *attributes, LinkContainer *links,
                         AppSettings *settings, uint proposedID);

    virtual ~RequirementReference();

    virtual bool isReference();
    virtual QString getTitle() const;
    virtual QString getNumberedTitle() const;
    virtual QTextDocument* getDescription();

    virtual void setTargetID(uint id);
    virtual uint getTargetID() const;

protected:
    uint targetID;
    shared_ptr<QTextDocument> refDescription;

    Requirement *getSource() const;
    void initialize(uint targetID, Type type);
};

#endif // REQUIREMENTREFERENCE_H
