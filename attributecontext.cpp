#include "attributecontext.h"

AttributeContext::AttributeContext()
{
}

AttributeContext::~AttributeContext()
{

}

QVariant AttributeContext::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        if(section == 0)
            return tr("Name");
        else if(section == 1)
            return tr("Data Type");
    }

    return QVariant();
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
            return typeString(attributes[row].type);
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

    emit attributeAboutToBeInserted(attributes.size() - 1);
    emit newAttribute(attributes.size() - 1);
    emit attributeInserted();
}

void AttributeContext::removeAttribute(int row)
{
    if(row < 0 || row >= attributes.size())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    attributes.remove(row);
    endRemoveRows();

    emit attributeAboutToBeRemoved(row);
    emit removedAttribute(row);
    emit attributeRemoved();
}


QString AttributeContext::name(int index) const
{
    return attributes[index].name;
}

AttributeContext::DataType AttributeContext::type(int index) const
{
    return attributes[index].type;
}

QString AttributeContext::typeString(int index) const
{
    return typeString(attributes[index].type);
}

QString AttributeContext::typeString(AttributeContext::DataType type) const
{
    switch(type){
    case BOOLEAN:
        return tr("Boolean");
    case TEXT:
        return tr("Text");
    }
}

