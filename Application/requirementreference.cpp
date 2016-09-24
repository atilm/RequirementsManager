#include <QDebug>
#include <QTextCursor>

#include "requirementreference.h"


RequirementReference::RequirementReference(uint targetID,
                                           Requirement::Type type,
                                           UniqueIDManager *idManager,
                                           RequirementRefCounter *refCounter,
                                           shared_ptr<RiskAssessmentModel> riskAssessment,
                                           AttributeContainer *attributes,
                                           LinkContainer *links,
                                           AppSettings *settings)
    : Requirement(idManager, refCounter, riskAssessment,
                  attributes, links, settings)
{
    initialize(targetID, type);
}

RequirementReference::RequirementReference(uint targetID,
                                           UniqueIDManager *idManager,
                                           RequirementRefCounter *refCounter,
                                           shared_ptr<RiskAssessmentModel> riskAssessment,
                                           AttributeContainer *attributes,
                                           LinkContainer *links,
                                           AppSettings *settings,
                                           uint proposedID)
    : Requirement(idManager, refCounter, riskAssessment,
                  attributes, links,
                  settings, proposedID)
{
    initialize(targetID, getType());
}

RequirementReference::~RequirementReference()
{
    refCounter->removeReference(targetID, id);

    delete refDescription;
}

bool RequirementReference::isReference()
{
    return true;
}

QString RequirementReference::getTitle() const
{
    Requirement *source = getSource();

    QString title = "[LINK] %1";
    if(source){
        title = title.arg(source->getTitle());
    }
    else{
        title = title.arg("UNRESOLVED");
    }

    return title;
}

QString RequirementReference::getNumberedTitle() const
{
    QString idString;
    if(settings->idIsVisible()){
        idString = QString("[%1] ").arg(id, 3, 10, QChar('0'));
    }

    QString title = "UNRESOLVED";

    Requirement *source = getSource();
    if(source){
        title = source->getTitle();
    }

    return QString("%1 %2[LINK] %3")
            .arg(number())
            .arg(idString)
            .arg(title);
}

QTextDocument *RequirementReference::getDescription()
{
    Requirement *source = getSource();

    if(refDescription){
        delete refDescription;
    }

    if(source){
        refDescription = source->getDescription()->clone();

        QString ref = QString("LINK to %1\n\n").arg(source->getNumberedTitle());

        QTextCursor cursor(refDescription);
        cursor.setPosition(0);
        cursor.insertText(ref);
    }
    else{
        refDescription = new QTextDocument();
        QString s = QString("UNRESOLVED LINK to [%1]").arg(targetID, 3, 10, QChar('0'));
        refDescription->setHtml(s);
    }

    return refDescription;
}

void RequirementReference::setTargetID(uint id)
{
    targetID = id;
}

uint RequirementReference::getTargetID() const
{
    return targetID;
}

Requirement *RequirementReference::getSource() const
{
    if(idManager->hasID(targetID)){
        return idManager->getRequirement(targetID);
    }
    else{
        return nullptr;
    }
}

void RequirementReference::initialize(uint targetID, Requirement::Type type)
{
    this->targetID = targetID;
    setType(type);
    refDescription = nullptr;

    // register yourself with the refernce counter:
    refCounter->addReference(targetID, id);
}
