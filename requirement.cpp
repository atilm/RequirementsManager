#include "requirement.h"

Requirement::Requirement(UniqueIDManager *idManager) :
    id(idManager->newUniqueID())
{
    this->idManager = idManager;
    parent = NULL;
    title = "Requirement";
}

Requirement::Requirement(UniqueIDManager *idManager, uint proposedID) :
    id(idManager->newUniqueID(proposedID))
{
    this->idManager = idManager;
    parent = NULL;
    title = "Requirement";
}

Requirement::~Requirement()
{
    idManager->removeID(id);

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

void Requirement::setDescription(const QString &d)
{
    description = d;
}

QString Requirement::getDescription()
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

int Requirement::indexOf(const Requirement *item) const
{
    for(int i=0;i<childCount();i++){
        if(item == children.at(i))
            return i;
    }
}

void Requirement::assertValidIndex(int index)
{
    if(index < 0 || index > children.size()-1)
        throw InvalidIndexException();
}
