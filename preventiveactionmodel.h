#ifndef PREVENTIVEACTIONMODEL_H
#define PREVENTIVEACTIONMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "preventiveaction.h"
#include "filestatetracker.h"

class PreventiveActionModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit PreventiveActionModel(FileStateTracker *fileState, QObject *parent = 0);
    virtual ~PreventiveActionModel();

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual PreventiveAction* appendAction();
    virtual void add(int beforeRowIndex);
    virtual void remove(const QModelIndex &index);
    virtual PreventiveAction* getAction(const QModelIndex &index);
signals:

public slots:

private:
    FileStateTracker *fileState;
    QVector<PreventiveAction*> actions;
};

#endif // PREVENTIVEACTIONMODEL_H
