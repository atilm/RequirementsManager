#ifndef REQUIREMENT_H
#define REQUIREMENT_H

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
    Requirement();
    virtual ~Requirement();

    virtual void setTitle(const QString &title);
    virtual QString getTitle() const;

    virtual QTextDocument* getDescription();

    virtual void setParent(Requirement *parent);
    virtual Requirement* getParent();
    virtual int getRow() const;

    virtual Requirement *getChild(int index);

    virtual int childCount() const;
    virtual void insertChildren(int beforeIndex, int count);
    virtual void appendChild();

    virtual int indexOf(const Requirement *item) const;

private:
    Requirement *parent;
    QVector<Requirement*> children;

    QString title;
    QTextDocument *description;
};

#endif // REQUIREMENT_H
