#include "requirementtomodelmapper.h"
#include <QColor>

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
                          Qt::ItemIsDragEnabled |
                          Qt::ItemIsDropEnabled;


    if(column > 0 && column  <= context->rowCount()){
        int attributeIndex = column - 1;

        if(context->type(attributeIndex) == AttributeContext::BOOLEAN){
            flags |= Qt::ItemIsUserCheckable;
        }
        else
            flags |= Qt::ItemIsEditable;
    }
    else if(column == 0)
        flags |= Qt::ItemIsEditable;

    return flags;
}

QVariant RequirementToModelMapper::getHeaderDisplayRole(int section,
                                                        Qt::Orientation orientation) const
{
    if(orientation == Qt::Horizontal){
        if(section == 0)
            return QObject::tr("Requirement");
        else if(section <= context->rowCount())
            return context->name(section - 1);
    }
    return QVariant();
}

QVariant RequirementToModelMapper::getForegroundRole(const Requirement *requirement,
                                                     int column) const
{
    if(column == 0){
        switch(requirement->getType()){
        case Requirement::Section:
            return QColor("#000000");
        case Requirement::TableRow:
            return QColor("#4CBB17");
        case Requirement::UserRequirement:
            return QColor("#000000");
        case Requirement::FunctionalRequirement:
            return QColor("#268bd2");
        case Requirement::DesignRequirement:
            return QColor("#d33682");
        }
    }
    else
        return QVariant();
}

QVariant RequirementToModelMapper::getDisplayRole(const Requirement *requirement,
                                                  int column) const
{
    if(column == 0)
        return requirement->getNumberedTitle();
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

QVariant RequirementToModelMapper::getEditRole(const Requirement *requirement,
                                               int column) const
{
    if(column == 0)
        return requirement->getTitle();
    else
        return getDisplayRole(requirement, column);
}

QVariant RequirementToModelMapper::getCheckStateRole(const Requirement *requirement,
                                                     int column) const
{
    if(column > 0 && column <= context->rowCount()){
        int attributeIndex = column - 1;
        if(context->type(attributeIndex) == AttributeContext::BOOLEAN)
            return requirement->getAttribute(attributeIndex).toInt();
    }

    return QVariant();
}

QVariant RequirementToModelMapper::getFontRole(const Requirement *requirement,
                                               int column) const
{
    if(column == 0 && requirement->getType() == Requirement::Section){
        QFont boldFont;
        boldFont.setBold(true);
        return boldFont;
    }
    else{
        return QVariant();
    }
}

bool RequirementToModelMapper::setEditRole(const QVariant &value,
                                           Requirement *requirement,
                                           int column)
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

bool RequirementToModelMapper::setCheckStateRole(const QVariant &value,
                                                 Requirement *requirement,
                                                 int column)
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


