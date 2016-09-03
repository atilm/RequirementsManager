#include "preventiveactionmodel.h"
#include "automatedtestreference.h"
#include "preventiveactionfactory.h"
#include <exception>
using namespace std;

PreventiveActionModel::PreventiveActionModel(shared_ptr<FileStateTracker> fileState,
                                             shared_ptr<PreventiveActionFactory> factory,
                                             QObject *parent) :
    QAbstractTableModel(parent)
{
    this->fileState = fileState;
    this->factory = factory;
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

shared_ptr<PreventiveAction> PreventiveActionModel::appendAction()
{
    add(rowCount());
    return getAction(index(rowCount()-1,0));
}

void PreventiveActionModel::appendReference(shared_ptr<AutomatedTestReference> ref)
{
    int row = rowCount();

    beginInsertRows(QModelIndex(), row, row);
    actions.append(ref);
    endInsertRows();
    fileState->setChanged(true);
}

void PreventiveActionModel::add(int beforeRowIndex)
{
    int beforeRow = 0;

    if(beforeRowIndex >= 0 && beforeRowIndex <= rowCount())
        beforeRow = beforeRowIndex;

    beginInsertRows(QModelIndex(), beforeRow, beforeRow);
    actions.insert(beforeRow, factory->newPreventiveAction());
    endInsertRows();
    fileState->setChanged(true);
}

void PreventiveActionModel::remove(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    beginRemoveRows(QModelIndex(), index.row(), index.row());

    actions.remove(index.row());
    endRemoveRows();
    fileState->setChanged(true);
}

shared_ptr<PreventiveAction> PreventiveActionModel::getAction(const QModelIndex &index)
{
    if(!index.isValid())
        throw runtime_error("Invalid preventive action index");

    return actions[index.row()];
}
