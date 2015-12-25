#ifndef LINKCONTROLLER_H
#define LINKCONTROLLER_H

#include <QObject>
#include <QTreeView>
#include <QToolButton>
#include <QDebug>

#include "requirementsview.h"
#include "descriptionview.h"

class LinkController : public QObject
{
    Q_OBJECT
public:
    explicit LinkController(QObject *parent = 0);
    virtual ~LinkController();

    virtual void setLinkView(QTreeView *view);
    virtual void setRequirementsView(RequirementsView *view);
    virtual void setDescriptionView(DescriptionView *view);
    virtual void setAddButton(QToolButton *button);
    virtual void setRemoveButton(QToolButton *button);

    virtual void setUpSelectionModeConnections();
    virtual void setUpAddModeConnections();
signals:

public slots:
    void handleCurrentRequirementChanged(const QModelIndex &current,
                                         const QModelIndex &previous);
    void handleAddButtonToggled(bool on);
    void handleRemoveButtonClicked();
    void handleAddRequirementLink(const QModelIndex &index);

private:
    QToolButton *addButton;
    QToolButton *removeButton;
    QTreeView *linkView;
    RequirementsView *reqView;
    DescriptionView *descriptionView;
    LinkContainer *currentLinks;

};

#endif // LINKCONTROLLER_H
