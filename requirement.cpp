#include "requirement.h"

Requirement::Requirement(UniqueIDManager *idManager, AttributeContainer *attributes) :
    id(idManager->newUniqueID())
{
    this->attributes = attributes;
    this->idManager = idManager;
    parent = NULL;

    title = "Requirement";
    description = new QTextDocument();
}

Requirement::Requirement(UniqueIDManager *idManager,
                         uint proposedID,
                         AttributeContainer *attributes) :
    id(idManager->newUniqueID(proposedID))
{
    this->attributes = attributes;
    this->idManager = idManager;
    parent = NULL;

    title = "Requirement";
    description = new QTextDocument();
}

Requirement::~Requirement()
{
    idManager->removeID(id);

    delete attributes;

    for(int i=0;i<childCount();i++)
        delete children[i];
}

uint Requirement::getID()
{
    return id;
}

void Requirement::setTitle(const QString &title)
{
    this->title = title;
}

QString Requirement::getTitle() const
{
    return title;
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

void Requirement::setParent(Requirement *parent)
{
    this->parent = parent;
}

Requirement *Requirement::getParent()
{
    return parent;
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

void Requirement::assertValidIndex(int index)
{
    if(index < 0 || index > children.size()-1)
        throw InvalidIndexException();
}
