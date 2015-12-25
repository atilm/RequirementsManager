#ifndef REQUIREMENT_H
#define REQUIREMENT_H

#include "uniqueidmanager.h"
#include "attributecontainer.h"
#include "linkcontainer.h"
#include "riskassessmentmodel.h"

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

    enum Type{
        UserRequirement,
        FunctionalRequirement,
        DesignRequirement
    };

    Requirement(UniqueIDManager *idManager, RiskAssessmentModel *riskAssessment,
                AttributeContainer *attributes, LinkContainer *links);
    Requirement(UniqueIDManager *idManager, RiskAssessmentModel *riskAssessment,
                AttributeContainer *attributes, LinkContainer *links,
                uint proposedID);
    virtual ~Requirement();

    virtual uint getID();

    virtual void setType(Type type);
    virtual Type getType() const;

    virtual void setParent(Requirement *parent);
    virtual Requirement* getParent();

    virtual QString number() const;
    virtual void setTitle(const QString &title);
    virtual QString getTitle() const;
    virtual QVariant getAttribute(int index) const;
    virtual void setAttribute(int index, const QVariant &value);

    virtual QTextDocument *getDescription();
    virtual RiskAssessmentModel* getRiskAssessment();
    virtual LinkContainer* getLinkContainer();

    virtual int getRow() const;

    virtual Requirement *getChild(int index);

    virtual int childCount() const;
    virtual void insertChild(int beforeIndex, Requirement *child);
    virtual void appendChild(Requirement *child);

    virtual void removeChild(int index);
    virtual Requirement* popChild(int index);

    virtual int indexOf(const Requirement *item) const;

    static QString typeToString(Type type);
    static Type stringToType(const QString &typeString);
private:
    const unsigned int id;

    Type type;
    UniqueIDManager *idManager;
    Requirement *parent;
    QVector<Requirement*> children;

    QString title;
    QTextDocument *description;
    AttributeContainer *attributes;
    LinkContainer *links;

    RiskAssessmentModel *riskAssessment;

    void assertValidIndex(int index);
};

#endif // REQUIREMENT_H
