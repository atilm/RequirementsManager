#include "requirementtomodelmapper.h"

RequirementToModelMapper::RequirementToModelMapper(AttributeContext *context)
{
    this->context = context;
}

int RequirementToModelMapper::columns() const
{
    return context->rowCount() + 1;
}

Qt::ItemFlags RequirementToModelMapper::flags(int column) const
{
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable |
                          Qt::ItemIsEditable | Qt::ItemIsDragEnabled |
                          Qt::ItemIsDropEnabled;

    if(column > 0 && column  <= context->rowCount()){
        int attributeIndex = column - 1;

        if(context->type(attributeIndex) == AttributeContext::BOOLEAN){
            flags |= Qt::ItemIsUserCheckable;
        }
    }

    return flags;
}

QVariant RequirementToModelMapper::getHeaderDisplayRole(int section, Qt::Orientation orientation) const
{
    if(orientation == Qt::Horizontal){
        if(section == 0)
            return QObject::tr("Requirement");
        else if(section <= context->rowCount())
            return context->name(section - 1);
    }
    return QVariant();
}

QVariant RequirementToModelMapper::getDisplayRole(const Requirement *requirement, int column) const
{
    if(column == 0)
        return requirement->getTitle();
    else if(column  <= context->rowCount()){
        int attributeIndex = column - 1;
        if(context->type(attributeIndex) == AttributeContext::BOOLEAN)
            return QVariant();
        else
            return requirement->getAttribute(attributeIndex);
    }
    else
        return QVariant();
}

QVariant RequirementToModelMapper::getEditRole(const Requirement *requirement, int column) const
{
    return getDisplayRole(requirement, column);
}

QVariant RequirementToModelMapper::getCheckStateRole(const Requirement *requirement, int column) const
{
    if(column > 0 && column <= context->rowCount()){
        int attributeIndex = column - 1;
        if(context->type(attributeIndex) == AttributeContext::BOOLEAN)
            return requirement->getAttribute(attributeIndex).toInt();
    }

    return QVariant();
}

bool RequirementToModelMapper::setEditRole(const QVariant &value, Requirement *requirement, int column)
{
    if(column == 0){
        requirement->setTitle(value.toString());
        return true;
    }
    else if(column <= context->rowCount()){
        int attributeIndex = column - 1;
        if(context->type(attributeIndex) == AttributeContext::BOOLEAN)
            return false;
        else{
            requirement->setAttribute(attributeIndex, value);
            return true;
        }
    }
    else
        return false;
}

bool RequirementToModelMapper::setCheckStateRole(const QVariant &value, Requirement *requirement, int column)
{
    if(column > 0 && column <= context->rowCount()){
        int attributeIndex = column - 1;
        if(context->type(attributeIndex) == AttributeContext::BOOLEAN){
            requirement->setAttribute(attributeIndex, value);
            return true;
        }
        else
            return false;
    }
    return false;
}


