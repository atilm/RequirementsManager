#ifndef SOURCENODE_H
#define SOURCENODE_H

#include <QVector>

class SourceNode
{
public:
    SourceNode();
    virtual ~SourceNode();

    virtual QString getName() const;

    virtual int childCount() const;
    virtual SourceNode *getChild(int index) const;
    virtual void appendChild(SourceNode *child);
    virtual void setParent(SourceNode *parent);
    virtual SourceNode *getParent() const;
    virtual int getRow();
    virtual int indexOf(SourceNode *child) const;

private:
    SourceNode *parent;
    QVector<SourceNode*> children;
};

#endif // SOURCENODE_H
