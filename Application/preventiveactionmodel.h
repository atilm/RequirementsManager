#ifndef PREVENTIVEACTIONMODEL_H
#define PREVENTIVEACTIONMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "preventiveaction.h"
#include "filestatetracker.h"

#include <memory>
using namespace std;

class AutomatedTestReference;
class PreventiveActionFactory;

class PreventiveActionModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit PreventiveActionModel(shared_ptr<FileStateTracker> fileState,
                                   shared_ptr<PreventiveActionFactory> factory,
                                   QObject *parent = 0);
    virtual ~PreventiveActionModel();

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual shared_ptr<PreventiveAction> appendAction();
    virtual void appendReference(shared_ptr<AutomatedTestReference> ref);
    virtual void add(int beforeRowIndex);
    virtual void remove(const QModelIndex &index);
    virtual shared_ptr<PreventiveAction> getAction(const QModelIndex &index);

private:
    shared_ptr<FileStateTracker> fileState;
    shared_ptr<PreventiveActionFactory> factory;
    QVector<shared_ptr<PreventiveAction>> actions;
};

#endif // PREVENTIVEACTIONMODEL_H
