#ifndef REQUIREMENTSMODEL_H
#define REQUIREMENTSMODEL_H

#include <QAbstractItemModel>
#include "requirement.h"
#include "requirementfactory.h"

class RequirementsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit RequirementsModel(RequirementFactory *factory,
                               QObject *parent = 0);

    virtual ~RequirementsModel();

    // required overriden functions
    virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const ;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex	parent(const QModelIndex & index) const;

    // additional overriden functions
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
    virtual bool insertColumns(int column, int count, const QModelIndex & parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
    virtual bool removeColumns(int column, int count, const QModelIndex & parent = QModelIndex());
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    // specific functions
    virtual bool appendSibling(const QModelIndex &index);
    virtual bool appendChild(const QModelIndex &index);

signals:

public slots:

private:
    RequirementFactory *factory;
    Requirement *root;

    Requirement *asRequirement(const QModelIndex &index) const;
    Requirement *getValidItem(const QModelIndex &index) const;
};

#endif // REQUIREMENTSMODEL_H
