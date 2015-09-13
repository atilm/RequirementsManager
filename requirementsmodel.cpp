#include "requirementsmodel.h"

RequirementsModel::RequirementsModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

int RequirementsModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

int RequirementsModel::rowCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant RequirementsModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QModelIndex RequirementsModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex RequirementsModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

QVariant RequirementsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

bool RequirementsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    return true;
}

bool RequirementsModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    return true;
}

bool RequirementsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    return true;
}

bool RequirementsModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    return true;
}

bool RequirementsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return true;
}


