#include "sourcecodemodel.h"

SourceCodeModel::SourceCodeModel()
{
    root = nullptr;
}

SourceCodeModel::~SourceCodeModel()
{

}

int SourceCodeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

int SourceCodeModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant SourceCodeModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QModelIndex SourceCodeModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex SourceCodeModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

QVariant SourceCodeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

Qt::ItemFlags SourceCodeModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

