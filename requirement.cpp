#include "requirement.h"
#include <QDebug>

Requirement::Requirement(UniqueIDManager *idManager, RiskAssessmentModel *riskAssessment,
                         AttributeContainer *attributes, LinkContainer *links) :
    id(idManager->newUniqueID())
{
    this->attributes = attributes;
    this->links = links;
    this->riskAssessment = riskAssessment;
    this->idManager = idManager;
    parent = NULL;

    type = UserRequirement;
    title = "Requirement";
    description = new QTextDocument();
}

Requirement::Requirement(UniqueIDManager *idManager, RiskAssessmentModel *riskAssessment,
                         AttributeContainer *attributes, LinkContainer *links,
                         uint proposedID) :
    id(idManager->newUniqueID(proposedID))
{
    this->attributes = attributes;
    this->links = links;
    this->riskAssessment = riskAssessment;
    this->idManager = idManager;
    parent = NULL;

    type = UserRequirement;
    title = "Requirement";
    description = new QTextDocument();
}

Requirement::~Requirement()
{
    idManager->removeID(id);

    delete riskAssessment;
    delete attributes;
    delete links;

    for(int i=0;i<childCount();i++)
        delete children[i];
}

uint Requirement::getID()
{
    return id;
}

void Requirement::setType(Requirement::Type type)
{
    this->type = type;
}

Requirement::Type Requirement::getType() const
{
    return type;
}

void Requirement::setTitle(const QString &title)
{
    this->title = title;
}

QString Requirement::getTitle() const
{
    return QString("%1 %2")
            .arg(number())
            .arg(title);
}

QVariant Requirement::getAttribute(int index) const
{
    return attributes->getField(index);
}

void Requirement::setAttribute(int index, const QVariant &value)
{
    attributes->setField(index, value);
}

QTextDocument *Requirement::getDescription()
{
    return description;
}

RiskAssessmentModel *Requirement::getRiskAssessment()
{
    return riskAssessment;
}

LinkContainer *Requirement::getLinkContainer()
{
    return links;
}

void Requirement::setParent(Requirement *parent)
{
    this->parent = parent;
}

Requirement *Requirement::getParent()
{
    return parent;
}

QString Requirement::number() const
{
    if(!parent)
        return "";

    int myNumber = parent->indexOf(this) + 1;
    QString parentNumber = parent->number();

    if(parentNumber.isEmpty())
        return QString("%1").arg(myNumber);
    else
        return QString("%1.%2")
                .arg(parentNumber)
                .arg(myNumber);
}

int Requirement::getRow() const
{
    if(parent != NULL)
        return parent->indexOf(this);
    else
        return 0;
}

Requirement *Requirement::getChild(int index)
{
    assertValidIndex(index);

    return children.at(index);
}

int Requirement::childCount() const
{
    return children.size();
}

void Requirement::insertChild(int beforeIndex, Requirement *child)
{
    if(beforeIndex <= childCount()){
        child->setParent(this);
        children.insert(beforeIndex, child);
    }
}

void Requirement::appendChild(Requirement *child)
{
    child->setParent(this);
    children.append(child);
}

void Requirement::removeChild(int index)
{
    assertValidIndex(index);

    delete children[index];
    children.remove(index);
}

Requirement *Requirement::popChild(int index)
{
    assertValidIndex(index);

    Requirement* child = children[index];
    children.remove(index);
    return child;
}

int Requirement::indexOf(const Requirement *item) const
{
    for(int i=0;i<childCount();i++){
        if(item == children.at(i))
            return i;
    }
    return -1;
}

QString Requirement::typeToString(Requirement::Type type)
{
    switch(type){
    case UserRequirement:
        return "UserRequirement";
    case FunctionalRequirement:
        return "FunctionalRequirement";
    case DesignRequirement:
        return "DesignRequirement";
    default:
        return "";
    }
}

Requirement::Type Requirement::stringToType(const QString &typeString)
{
    if(typeString == "DesignRequirement")
        return DesignRequirement;
    else if(typeString == "FunctionalRequirement")
        return FunctionalRequirement;
    else
        return UserRequirement;
}

void Requirement::assertValidIndex(int index)
{
    if(index < 0 || index > children.size()-1){
        throw InvalidIndexException();
    }
}
