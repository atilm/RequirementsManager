#ifndef REQUIREMENTTOMODELMAPPER_H
#define REQUIREMENTTOMODELMAPPER_H

#include <QAbstractItemModel>
#include "requirement.h"
#include "attributecontext.h"

class RequirementsModel;

//! Encapsulates communication of RequirementsModel and individual requirements
/*!
  - Returns the correct flags for all columns
  - Returns the correct data for all columns and roles
  - Sets the data correctly for all columns and roles
*/
class RequirementToModelMapper
{
public:
    RequirementToModelMapper(AttributeContext *context);

    int columns() const;

    Qt::ItemFlags flags(int column) const;

    QVariant getHeaderDisplayRole(int section, Qt::Orientation orientation) const;

    QVariant getForegroundRole(const Requirement *requirement, int column) const;
    QVariant getDisplayRole(const Requirement *requirement, int column) const;
    QVariant getEditRole(const Requirement *requirement, int column) const;
    QVariant getCheckStateRole(const Requirement *requirement, int column) const;

    bool setEditRole(const QVariant &value, Requirement *requirement, int column);
    bool setCheckStateRole(const QVariant &value, Requirement *requirement, int column);

private:
    AttributeContext *context;
};

#endif // REQUIREMENTTOMODELMAPPER_H
