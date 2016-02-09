#ifndef SOURCENODE_H
#define SOURCENODE_H

#include <QVector>

class SourceNode
{
public:
    SourceNode();
    virtual ~SourceNode();

private:
    SourceNode *parent;
    QVector<SourceNode*> children;
};

#endif // SOURCENODE_H
