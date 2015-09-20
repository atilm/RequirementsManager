#ifndef REQUIREMENTSVIEW_H
#define REQUIREMENTSVIEW_H

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

private:
    RequirementsModel *requirementsModel();

};

#endif // REQUIREMENTSVIEW_H
