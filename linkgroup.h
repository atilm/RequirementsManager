#ifndef LINKGROUP_H
#define LINKGROUP_H

#include <QVector>

#include "linknode.h"

class LinkGroup : public LinkNode
{
public:
    LinkGroup();

    virtual QString getName() const;
    virtual void setName(const QString &name);

    virtual QString toString() const;

private:
    QString name;
};

#endif // LINKGROUP_H
