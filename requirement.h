#ifndef REQUIREMENT_H
#define REQUIREMENT_H

#include "uniqueidmanager.h"

#include <QTextDocument>
#include <QVector>
#include <exception>
using namespace std;

class InvalidIndexException : public exception{

};

//! A requirements tree node
/*!
  This class implements a tree of requirements.
  Each tree node represents one requirement with a
  titel and a rich-text description.
 */
class Requirement
{
public:
    Requirement(UniqueIDManager *idManager);
    Requirement(UniqueIDManager *idManager, uint proposedID);
    virtual ~Requirement();

    virtual uint getID();

    virtual void setParent(Requirement *parent);
    virtual Requirement* getParent();

    virtual void setTitle(const QString &title);
    virtual QString getTitle() const;

    virtual QTextDocument *getDescription();

    virtual int getRow() const;

    virtual Requirement *getChild(int index);

    virtual int childCount() const;
    virtual void insertChild(int beforeIndex, Requirement *child);
    virtual void appendChild(Requirement *child);

    virtual void removeChild(int index);
    virtual Requirement* popChild(int index);

    virtual int indexOf(const Requirement *item) const;


private:
    const unsigned int id;

    UniqueIDManager *idManager;
    Requirement *parent;
    QVector<Requirement*> children;

    QString title;
    QTextDocument *description;

    void assertValidIndex(int index);
};

#endif // REQUIREMENT_H
