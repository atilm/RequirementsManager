#ifndef REQUIREMENTSMODEL_H
#define REQUIREMENTSMODEL_H

#include <QAbstractItemModel>
#include "requirement.h"
#include "requirementfactory.h"
#include "filestatetracker.h"
#include <exception>

class InvalidModelIndexException : public std::exception{

};

class RequirementsModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit RequirementsModel(RequirementFactory *factory,
                               FileStateTracker *fileState,
                               QObject *parent = 0);

    virtual ~RequirementsModel();

    virtual void init();
    virtual void clearModel();

    // required overriden functions
    virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const ;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex	parent(const QModelIndex & index) const;

    // additional overriden functions
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    // specific functions
    virtual QModelIndex appendSibling(const QModelIndex &index);
    virtual QModelIndex appendChild(const QModelIndex &index);
    virtual bool removeRequirement(const QModelIndex &index);

    virtual QTextDocument* getDescription(const QModelIndex &index);

    virtual uint getID(const QModelIndex &index);
signals:

public slots:

private:
    RequirementFactory *factory;
    Requirement *root;
    FileStateTracker *fileState;

    Requirement *asRequirement(const QModelIndex &index) const;
    Requirement *getValidItem(const QModelIndex &index) const;

private slots:
    void handleDescriptionChanged();
};

#endif // REQUIREMENTSMODEL_H
