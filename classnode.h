#ifndef CLASSNODE_H
#define CLASSNODE_H

#include "sourcenode.h"

class ClassNode : public SourceNode
{
public:
    ClassNode();
    virtual ~ClassNode();

    virtual void setName(const QString &name);
    virtual QString getName() const;

private:
    QString name;
};

#endif // CLASSNODE_H
