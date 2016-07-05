#ifndef DIRECTORYLISTMODEL_H
#define DIRECTORYLISTMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include "filestatetracker.h"

class DirectoryListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit DirectoryListModel(shared_ptr<FileStateTracker> fileState,
                                QObject *parent = 0);
    virtual ~DirectoryListModel();

    virtual void clear();

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual QString absolutePath(int idx) const;

    virtual void add(const QString &directoryPath);
    virtual bool remove(const QModelIndex &index);

private:
    shared_ptr<FileStateTracker> fileState;
    QVector<QString> directories;
};

#endif // DIRECTORYLISTMODEL_H
