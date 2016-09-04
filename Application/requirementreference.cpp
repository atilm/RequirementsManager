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
    this->source = source;
    refDescription = make_shared<QTextDocument>();
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

    return QString("%1 %2[LINK] %3")
            .arg(number())
            .arg(idString)
            .arg(source->getTitle());
}

QTextDocument *RequirementReference::getDescription()
{
    QString html = source->getDescription()->toHtml();
    QString ref = QString("LINK to %1").arg(source->getNumberedTitle());
    QString s = QString("%1<br>\n%2").arg(ref).arg(html);

    refDescription->setHtml(s);
    return refDescription.get();
}

uint RequirementReference::getTargetID() const
{
    return source->getID();
}
