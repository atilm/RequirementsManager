#include "requirementreference.h"

RequirementReference::RequirementReference(Requirement *source,
                                           UniqueIDManager *idManager,
                                           shared_ptr<RiskAssessmentModel> riskAssessment,
                                           AppSettings *settings)
    : Requirement(idManager, riskAssessment,
                  source->getAttributeContainer(),
                  source->getLinkContainer(),
                  settings)
{
    initialize(source->getID(), source->getType());
}

RequirementReference::RequirementReference(uint targetID,
                                           UniqueIDManager *idManager,
                                           shared_ptr<RiskAssessmentModel> riskAssessment,
                                           AttributeContainer *attributes,
                                           LinkContainer *links,
                                           AppSettings *settings,
                                           uint proposedID)
    : Requirement(idManager, riskAssessment,
                  attributes, links,
                  settings, proposedID)
{
    initialize(targetID, getType());
}

RequirementReference::~RequirementReference()
{

}

bool RequirementReference::isReference()
{
    return true;
}

QString RequirementReference::getNumberedTitle() const
{
    QString idString;
    if(settings->idIsVisible()){
        idString = QString("[%1] ").arg(id, 3, 10, QChar('0'));
    }

    QString title = "UNRESOLVED";
    if(idManager->hasID(targetID))
    {
        title = idManager->getRequirement(targetID)->getTitle();
    }

    return QString("%1 %2[LINK] %3")
            .arg(number())
            .arg(idString)
            .arg(title);
}

QTextDocument *RequirementReference::getDescription()
{
    QString s = QString("UNRESOLVED LINK to [%1]").arg(targetID, 3, 10, QChar('0'));

    if(idManager->hasID(targetID)){
        Requirement *source = idManager->getRequirement(targetID);
        QString html = source->getDescription()->toHtml();
        QString ref = QString("LINK to %1").arg(source->getNumberedTitle());
        s = QString("%1<br>\n%2").arg(ref).arg(html);
    }

    refDescription->setHtml(s);
    return refDescription.get();
}

void RequirementReference::setTargetID(uint id)
{
    targetID = id;
}

uint RequirementReference::getTargetID() const
{
    return targetID;
}

void RequirementReference::initialize(uint targetID, Requirement::Type type)
{
    this->targetID = targetID;
    setType(type);
    refDescription = make_shared<QTextDocument>();
}
