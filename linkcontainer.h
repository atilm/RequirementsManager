#ifndef LINKCONTAINER_H
#define LINKCONTAINER_H

#include <QAbstractItemModel>

#include "linkcontext.h"

class LinkContainer : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit LinkContainer(LinkContext *context, QObject *parent = 0);
    virtual ~LinkContainer();

    // required overriden functions
    virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const ;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex	parent(const QModelIndex & index) const;

signals:

public slots:

private:
    LinkContext *context;
};

#endif // LINKCONTAINER_H
