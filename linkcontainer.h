#ifndef LINKCONTAINER_H
#define LINKCONTAINER_H

#include <QAbstractItemModel>
#include <QVector>

#include "linkcontext.h"
#include "linknode.h"
#include "linkgroup.h"
#include "linktorequirement.h"
#include "uniqueidmanager.h"

class Requirement;

class LinkContainer : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit LinkContainer(LinkContext *context,
                           UniqueIDManager *idManager,
                           QObject *parent = 0);
    virtual ~LinkContainer();
    virtual void setOwner(Requirement *r);

    // required overriden functions
    virtual int columnCount(const QModelIndex &parent) const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const ;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    LinkGroup* getLinkGroup(int row) const;
signals:

public slots:
    virtual void handleLinkTypeInserted(int before);
    virtual void handleLinkTypeRemoved(int index);
    virtual void handleRequirementRemoved(unsigned int id);
    virtual void addLink(const QModelIndex &index,
                         LinkToRequirement *link);
    virtual void addLink(int groupIdx, unsigned int requirementID);
    virtual void removeLink(const QModelIndex &index);

private:
    Requirement *owner;
    LinkNode *root;
    LinkContext *context;
    UniqueIDManager *idManager;

    void initialize();

    void connectSignals();
    LinkNode* getValidItem(const QModelIndex &index) const;
    LinkNode* asLinkNode(const QModelIndex &index) const;
    LinkGroup* asLinkGroup(const QModelIndex &index) const;
    LinkToRequirement* asLinkToRequirement(const QModelIndex &index) const;
    QString requirementIDToString(unsigned int id) const;
};

#endif // LINKCONTAINER_H
