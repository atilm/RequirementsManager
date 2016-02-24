#ifndef DESIGNREFERENCE_H
#define DESIGNREFERENCE_H

#include "sourcecodemodel.h"
#include "requirement.h"

class SourceCodeController;

class DesignReference : public Requirement
{
public:
    DesignReference(SourceAddress address, SourceCodeController *controller,
                    UniqueIDManager *idManager, RiskAssessmentModel *riskAssessment,
                    AttributeContainer *attributes, LinkContainer *links);

    DesignReference(SourceAddress address, SourceCodeController *controller,
                    UniqueIDManager *idManager, RiskAssessmentModel *riskAssessment,
                    AttributeContainer *attributes, LinkContainer *links,
                    unsigned int proposedID);

    virtual QTextDocument *getDescription();

private:
    SourceAddress address;
    SourceCodeController *controller;

    void initialize(SourceAddress address,
                    SourceCodeController *controller);
};

#endif // DESIGNREFERENCE_H
