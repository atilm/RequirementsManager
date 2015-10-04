#include "attributecontext.h"

AttributeContext::AttributeContext()
{
}

AttributeContext::~AttributeContext()
{

}

void AttributeContext::addAttribute(const QString &name, AttributeContext::DataType type)
{
    attributes[name] = type;

    emit newAttribute(name, type);
}

void AttributeContext::removeAttribute(const QString &name)
{
    if( attributes.remove(name) > 0 )
        emit removedAttribute(name);
}

int AttributeContext::count() const
{
    return attributes.count();
}

QList<QString> AttributeContext::names() const
{
    return attributes.keys();
}

AttributeContext::DataType AttributeContext::type(const QString &name) const
{
    return attributes[name];
}

QString AttributeContext::typeString(const QString &name) const
{
    switch(attributes[name]){
    case BOOLEAN:
        return tr("Boolean");
    case INTEGER:
        return tr("Integer");
    case TEXT:
        return tr("Text");
    }
}

