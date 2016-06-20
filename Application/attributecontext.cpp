#include "attributecontext.h"
#include <QDebug>

AttributeContext::AttributeContext(FileStateTracker *fileState)
{
    this->fileState = fileState;
    booleanTypeString = tr("Boolean");
    textTypeString = tr("Text");
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

void AttributeContext::clear()
{
    int rows = rowCount();


    for(int a=0;a<rows;a++)
        removeAttribute(0);
}

void AttributeContext::addAttribute(const QString &name, DataType type)
{
    Attribute a;
    a.name = name;
    a.type = type;

    beginInsertRows(QModelIndex(), attributes.size(), attributes.size());
    attributes.append(a);
    endInsertRows();

    fileState->setChanged(true);
    emit attributeAboutToBeInserted(attributes.size() - 1);
    emit newAttribute(attributes.size() - 1);
    emit attributeInserted();
}

void AttributeContext::addAttribute(const QString &name, const QString &typeString)
{
    DataType type = stringToDataType(typeString);

    addAttribute(name, type);
}

void AttributeContext::removeAttribute(int row)
{
    if(row < 0 || row >= attributes.size())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    attributes.remove(row);
    endRemoveRows();

    fileState->setChanged(true);
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
        return booleanTypeString;
    case TEXT:
        return textTypeString;
    default:
        return "";
    }
}

AttributeContext::DataType AttributeContext::stringToDataType(const QString &typeString)
{
    if(typeString == booleanTypeString)
        return BOOLEAN;
    else if(typeString == textTypeString)
        return TEXT;
    else
        return INVALID;
}

