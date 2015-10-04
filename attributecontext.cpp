#include "attributecontext.h"

AttributeContext::AttributeContext()
{
}

AttributeContext::~AttributeContext()
{

}

int AttributeContext::rowCount(const QModelIndex &parent) const
{
    return attributes.size();
}

int AttributeContext::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant AttributeContext::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole){
        int row = index.row();
        int col = index.column();

        if(col == 0)
            return attributes[row].name;
        else if(col == 1)
            return attributes[row].type;
        else
            return QVariant();
    }
    else
        return QVariant();
}

void AttributeContext::addAttribute(const QString &name, AttributeContext::DataType type)
{
    Attribute a;
    a.name = name;
    a.type = type;

    beginInsertRows(QModelIndex(), attributes.size(), attributes.size());
    attributes.append(a);
    endInsertRows();

    emit newAttribute(name, type);
}

void AttributeContext::removeAttribute(int row)
{
    if(row < 0 || row >= attributes.size())
        return;

    QString name = attributes[row].name;

    beginRemoveRows(QModelIndex(), row, row);
    attributes.remove(row);
    endRemoveRows();

    emit removedAttribute(name);
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
    return typeString(attributes[name]);
}

QString AttributeContext::typeString(AttributeContext::DataType type) const
{
    switch(type){
    case BOOLEAN:
        return tr("Boolean");
    case INTEGER:
        return tr("Integer");
    case TEXT:
        return tr("Text");
    }
}

