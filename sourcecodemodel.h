#ifndef SOURCECODEMODEL_H
#define SOURCECODEMODEL_H

#include <QAbstractItemModel>

#include "sourcenode.h"

class SourceCodeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    SourceCodeModel();
    virtual ~SourceCodeModel();

    // required overriden functions
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QModelIndex	index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex	parent(const QModelIndex &index) const;

    // additional overriden functions
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    SourceNode *root;

    SourceNode *asSourceNode(const QModelIndex &index) const;
    SourceNode *getValidItem(const QModelIndex &index) const;
};

#endif // SOURCECODEMODEL_H
