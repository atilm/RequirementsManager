#include "requirement.h"

Requirement::Requirement(unsigned int _id) : id(_id)
{
    parent = NULL;
    title = "Requirement";
    description = new QTextDocument();
}

Requirement::~Requirement()
{
    delete description;
}

void Requirement::setTitle(const QString &title)
{
    this->title = title;
}

QString Requirement::getTitle() const
{
    return title;
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
    if(index < 0 || index > children.size()-1)
        throw InvalidIndexException();
    else
        return children.at(index);
}

int Requirement::childCount() const
{
    return children.size();
}

void Requirement::insertChild(int beforeIndex, Requirement *item)
{
    if(beforeIndex <= childCount()){
        item->setParent(this);
        children.insert(beforeIndex, item);
    }
}

void Requirement::appendChild(Requirement *item)
{
    item->setParent(this);
    children.append(item);
}

int Requirement::indexOf(const Requirement *item) const
{
    for(int i=0;i<childCount();i++){
        if(item == children.at(i))
            return i;
    }
}
