#include "attributecontainer.h"

AttributeContainer::AttributeContainer(AttributeContext *context)
{
    this->context = context;

    initialize();

    connect(context, SIGNAL(newAttribute(int)), this, SLOT(attributeAdded(int)));
    connect(context, SIGNAL(removedAttribute(int)), this, SLOT(attributeRemoved(int)));
}

AttributeContainer::~AttributeContainer()
{

}

int AttributeContainer::count() const
{
    return attributes.size();
}

void AttributeContainer::setField(int index, const QVariant &value)
{
    attributes[index] = value;
}

QVariant AttributeContainer::getField(int index) const
{
    return attributes[index];
}

void AttributeContainer::initialize()
{
    for(int i=0;i<context->rowCount();i++)
        attributes.append(QVariant());
}

void AttributeContainer::attributeAdded(int beforeIndex)
{
    attributes.insert(beforeIndex, QVariant());
}

void AttributeContainer::attributeRemoved(int index)
{
    attributes.remove(index);
}
