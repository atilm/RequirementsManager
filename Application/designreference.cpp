#include "designreference.h"
#include "sourcecodecontroller.h"

DesignReference::DesignReference(SourceAddress address,
                                 SourceCodeController *controller,
                                 UniqueIDManager *idManager,
                                 RequirementRefCounter *refCounter,
                                 shared_ptr<RiskAssessmentModel> riskAssessment,
                                 AttributeContainer *attributes,
                                 LinkContainer *links,
                                 AppSettings *settings)
    : Requirement(idManager, refCounter, riskAssessment, attributes, links, settings)
{
    initialize(address, controller);
}

DesignReference::DesignReference(SourceAddress address,
                                 SourceCodeController *controller,
                                 UniqueIDManager *idManager,
                                 RequirementRefCounter *refCounter,
                                 shared_ptr<RiskAssessmentModel> riskAssessment,
                                 AttributeContainer *attributes,
                                 LinkContainer *links, AppSettings *settings,
                                 unsigned int proposedID)
    : Requirement(idManager, refCounter, riskAssessment, attributes, links, settings, proposedID)
{
    initialize(address, controller);
}

bool DesignReference::isReference() const
{
    return true;
}

SourceAddress DesignReference::getAddress()
{
    return address;
}

QTextDocument *DesignReference::getDescription()
{
    return controller->getDescription(address);
}

void DesignReference::initialize(SourceAddress address,
                                 SourceCodeController *controller)
{
    this->address = address;
    this->controller = controller;

    type = DesignRequirement;

    title = address.className;

    if(!address.functionName.isEmpty())
        title += QString("::%1").arg(address.functionName);
}

