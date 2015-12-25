#ifndef LINKCONTAINER_H
#define LINKCONTAINER_H

#include <QAbstractItemModel>
#include <QVector>

#include "linkcontext.h"
#include "linknode.h"

class LinkContainer : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit LinkContainer(LinkContext *context, QObject *parent = 0);
    virtual ~LinkContainer();

    // required overriden functions
    virtual int columnCount(const QModelIndex &parent) const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const ;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
signals:

public slots:
    virtual void handleLinkTypeInserted(int before);
    virtual void handleLinkTypeRemoved(int index);

private:
    LinkNode *root;
    LinkContext *context;

    void initialize();

    LinkNode* getValidItem(const QModelIndex &index) const;
    LinkNode* asLinkNode(const QModelIndex &index) const;
};

#endif // LINKCONTAINER_H
