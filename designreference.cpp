#include "designreference.h"
#include "sourcecodecontroller.h"

DesignReference::DesignReference(SourceAddress address, SourceCodeController *controller,
                                 UniqueIDManager *idManager,
                                 RiskAssessmentModel *riskAssessment,
                                 AttributeContainer *attributes,
                                 LinkContainer *links)
    : Requirement(idManager, riskAssessment, attributes, links)
{
    initialize(address, controller);
}

DesignReference::DesignReference(SourceAddress address,
                                 SourceCodeController *controller,
                                 UniqueIDManager *idManager,
                                 RiskAssessmentModel *riskAssessment,
                                 AttributeContainer *attributes,
                                 LinkContainer *links,
                                 unsigned int proposedID)
    : Requirement(idManager, riskAssessment, attributes, links, proposedID)
{
    initialize(address, controller);
}

bool DesignReference::isReference()
{
    return true;
}

SourceAddress DesignReference::getAddress()
{
    return address;
}

QTextDocument *DesignReference::getDescription()
{
    description->setPlainText(controller->getDescription(address));
    return description;
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

