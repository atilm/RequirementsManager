#ifndef REQUIREMENTREFVIEW_H
#define REQUIREMENTREFVIEW_H

#include "requirement.h"
#include "requirementsmodel.h"

#include <QListWidget>

#include <memory>
using namespace std;


class RequirementRefView : public QListWidget
{
    Q_OBJECT
public:
    RequirementRefView(QWidget *parent = 0);
    virtual ~RequirementRefView();

    virtual void setModel(shared_ptr<RequirementsModel> model);

public slots:
    virtual void switchItem(const QModelIndex &current, const QModelIndex &);
    virtual void showItem(const QModelIndex &index);

private:
    shared_ptr<RequirementsModel> model;

    virtual void setReferenceList(QList<Requirement*> refs);
};

#endif // REQUIREMENTREFVIEW_H
