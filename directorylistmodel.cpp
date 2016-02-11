#include "directorylistmodel.h"

DirectoryListModel::DirectoryListModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

DirectoryListModel::~DirectoryListModel()
{

}

void DirectoryListModel::clear()
{
    int rows = rowCount();

    for(int i=0;i<rows;i++)
        remove(index(0,0));
}

QVariant DirectoryListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

int DirectoryListModel::rowCount(const QModelIndex &parent) const
{
    return directories.count();
}

QVariant DirectoryListModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole){
        int row = index.row();
        return directories[row];
    }
    else
        return QVariant();
}

void DirectoryListModel::add(const QString &directoryPath)
{
    beginInsertRows(QModelIndex(), directories.count(), directories.count());
    directories.append(directoryPath);
    endInsertRows();
}

void DirectoryListModel::remove(const QModelIndex &index)
{
    if(index.isValid()){
        beginRemoveRows(QModelIndex(), index.row(), index.row());
        directories.remove(index.row());
        endRemoveRows();
    }
}

