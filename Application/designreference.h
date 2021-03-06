#ifndef DESIGNREFERENCE_H
#define DESIGNREFERENCE_H

#include "appsettings.h"
#include "sourcecodemodel.h"
#include "requirement.h"

class SourceCodeController;

class DesignReference : public Requirement
{
public:
    DesignReference(SourceAddress address,
                    SourceCodeController *controller,
                    UniqueIDManager *idManager,
                    RequirementRefCounter *refCounter,
                    shared_ptr<RiskAssessmentModel> riskAssessment,
                    AttributeContainer *attributes,
                    LinkContainer *links,
                    AppSettings *settings);

    DesignReference(SourceAddress address,
                    SourceCodeController *controller,
                    UniqueIDManager *idManager,
                    RequirementRefCounter *refCounter,
                    shared_ptr<RiskAssessmentModel> riskAssessment,
                    AttributeContainer *attributes,
                    LinkContainer *links,
                    AppSettings *settings,
                    unsigned int proposedID);

    virtual bool isReference();
    virtual SourceAddress getAddress();
    virtual QTextDocument *getDescription();

private:
    SourceAddress address;
    SourceCodeController *controller;

    void initialize(SourceAddress address,
                    SourceCodeController *controller);
};

#endif // DESIGNREFERENCE_H
