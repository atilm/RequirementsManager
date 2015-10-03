#ifndef REQUIREMENTSVIEW_H
#define REQUIREMENTSVIEW_H

#include <QDropEvent>
#include <QTreeView>
#include "requirementsmodel.h"

class RequirementsView : public QTreeView
{
    Q_OBJECT
public:
    explicit RequirementsView(QWidget *parent = 0);

signals:

public slots:
    virtual void insertSibling();
    virtual void appendChild();
    virtual void removeCurrent();

protected:
    virtual void startDrag(Qt::DropActions supportedActions);
    virtual void dropEvent(QDropEvent *event);

private:
    QModelIndex currentlyDragged;

    RequirementsModel *requirementsModel();

};

#endif // REQUIREMENTSVIEW_H
