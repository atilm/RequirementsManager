#ifndef LINKCONTROLLER_H
#define LINKCONTROLLER_H

#include <QObject>
#include <QTreeView>
#include <QToolButton>
#include <QDebug>

#include "requirementsview.h"

class LinkController : public QObject
{
    Q_OBJECT
public:
    explicit LinkController(QObject *parent = 0);
    virtual ~LinkController();

    virtual void setLinkView(QTreeView *view);
    virtual void setRequirementsView(RequirementsView *view);

    virtual void setUpConnections();
signals:

public slots:
    void handleCurrentRequirementChanged(const QModelIndex &current,
                                         const QModelIndex &previous);

private:
    QTreeView *linkView;
    RequirementsView *reqView;

};

#endif // LINKCONTROLLER_H
