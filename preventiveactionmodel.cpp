#include "preventiveactionmodel.h"
#include <exception>
using namespace std;

PreventiveActionModel::PreventiveActionModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

PreventiveActionModel::~PreventiveActionModel()
{

}

QVariant PreventiveActionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        if(section == 0)
            return tr("Action");
    }

    return QVariant();
}

int PreventiveActionModel::rowCount(const QModelIndex &parent) const
{
    return actions.count();
}

int PreventiveActionModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant PreventiveActionModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole){
        return actions[index.row()]->getShortAction();
    }

    return QVariant();
}

void PreventiveActionModel::add(const QModelIndex &beforeIndex)
{
    int beforeRow = 0;

    if(beforeIndex.isValid())
        beforeRow = beforeIndex.row();

    beginInsertRows(QModelIndex(), beforeRow, beforeRow);
    actions.insert(beforeRow, new PreventiveAction());
    endInsertRows();
}

void PreventiveActionModel::remove(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    beginRemoveRows(QModelIndex(), index.row(), index.row());
    actions.remove(index.row());
    endRemoveRows();
}

PreventiveAction *PreventiveActionModel::getAction(const QModelIndex &index)
{
    if(!index.isValid())
        throw runtime_error("Invalid preventive action index");

    return actions[index.row()];
}
