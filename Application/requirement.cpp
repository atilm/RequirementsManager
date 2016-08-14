#include "requirement.h"
#include <QDebug>

Requirement::Requirement(UniqueIDManager *idManager, shared_ptr<RiskAssessmentModel> riskAssessment,
                         AttributeContainer *attributes, LinkContainer *links) :
    id(idManager->newUniqueID())
{
    initialize(idManager, riskAssessment, attributes, links);
}

Requirement::Requirement(UniqueIDManager *idManager, shared_ptr<RiskAssessmentModel> riskAssessment,
                         AttributeContainer *attributes, LinkContainer *links,
                         unsigned int proposedID) :
    id(idManager->newUniqueID(proposedID))
{
    initialize(idManager, riskAssessment, attributes, links);
}

Requirement::~Requirement()
{
    idManager->removeID(id);

    delete description;
    delete attributes;
    delete links;

    foreach(Requirement *child, children)
        delete child;
}

uint Requirement::getID()
{
    return id;
}

bool Requirement::isReference()
{
    return false;
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
    return title;
}

QString Requirement::getNumberedTitle() const
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

shared_ptr<RiskAssessmentModel> Requirement::getRiskAssessment()
{
    return riskAssessment;
}

LinkContainer *Requirement::getLinkContainer()
{
    return links;
}

void Requirement::addRequirementLink(int groupIdx, uint reqID)
{
    links->addLink(groupIdx, reqID);
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

    int myNumber = parent->displayIndexOf(this);
    QString parentNumber = parent->number();

    QString numberString;

    if(parentNumber.isEmpty())
        numberString = QString("%1").arg(myNumber);
    else
        numberString = QString("%1.%2")
                .arg(parentNumber)
                .arg(myNumber);

    if(type == DesignRequirement)
        numberString = QString("DS.") + numberString;

    return numberString;
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

int Requirement::displayIndexOf(const Requirement *item) const
{
    Type type = item->getType();

    int currentIndex = 0;

    foreach(Requirement *child, children){
        if(sameTypeGroup(child->getType(), type))
            currentIndex++;
        if(child == item)
            return currentIndex;
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

void Requirement::initialize(UniqueIDManager *idManager,
                             shared_ptr<RiskAssessmentModel> riskAssessment,
                             AttributeContainer *attributes,
                             LinkContainer *links)
{
    this->attributes = attributes;
    this->links = links;
    this->links->setOwner(this);
    this->riskAssessment = riskAssessment;
    this->idManager = idManager;
    this->idManager->setRequirement(id, this);
    parent = nullptr;

    type = UserRequirement;
    title = "Requirement";
    description = new QTextDocument();
}

bool Requirement::sameTypeGroup(Requirement::Type a, Requirement::Type b) const
{
    if(a == DesignRequirement && b == DesignRequirement)
        return true;
    else if(a != DesignRequirement && b != DesignRequirement)
        return true;
    else
        return false;
}
