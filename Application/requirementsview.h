#ifndef REQUIREMENTSVIEW_H
#define REQUIREMENTSVIEW_H

#include <QDropEvent>
#include <QTreeView>
#include <QMenu>

#include "qmessageboxprovider.h"
#include "requirementsmodel.h"

#include <memory>
using namespace std;

class RequirementsView : public QTreeView
{
    Q_OBJECT
public:
    explicit RequirementsView(QMessageBoxProvider *msg,
                              QMenu *contextMenu,
                              QWidget *parent = 0);
    virtual ~RequirementsView();

    virtual void setModel(shared_ptr<RequirementsModel> model);

signals:

public slots:
    virtual void insertSibling();
    virtual void appendChild();
    virtual void appendChild(Requirement *item);
    virtual void removeCurrent();
    virtual void resizeColumns();

protected:
    virtual void startDrag(Qt::DropActions supportedActions);
    virtual void dropEvent(QDropEvent *event);
    virtual bool edit(const QModelIndex &index,
                      EditTrigger trigger, QEvent *event);

private:
    QMenu *contextMenu;
    QModelIndex currentlyDragged;
    QMessageBoxProvider *msg;

    RequirementsModel *requirementsModel();
    void setUpContextMenu(QMenu *contextMenu);

private slots:
    void handleCustomContextMenu(QPoint point);
    void handleToUserRequirement();
    void handleToFunctionalRequirement();
    void handleToDesignRequirement();
    void handleCreateReference();
};

#endif // REQUIREMENTSVIEW_H
