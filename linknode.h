#ifndef LINKNODE_H
#define LINKNODE_H

#include <QVector>

class LinkNode
{
public:
    LinkNode();

    virtual QString toString() const;
    virtual LinkNode* getChild(int index);
    virtual LinkNode* getParent();
    virtual int childCount() const;
    virtual void insertChild(LinkNode* node,
                             int before);
    virtual void removeChildAt(int index);
    virtual void setParent(LinkNode *parent);
    virtual int getRow();
    virtual int indexOf(const LinkNode *node) const;

private:
    LinkNode *parent;
    QVector<LinkNode*> children;

    bool isValidIndex(int index) const;
};

#endif // LINKNODE_H
