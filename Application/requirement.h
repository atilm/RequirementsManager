#ifndef REQUIREMENT_H
#define REQUIREMENT_H

#include "appsettings.h"
#include "attributecontainer.h"
#include "uniqueidmanager.h"
#include "linkcontainer.h"
#include "requirementrefcounter.h"
#include "riskassessmentmodel.h"

#include <QTextDocument>
#include <QVector>
#include <exception>
#include <memory>
using namespace std;

class InvalidIndexException : public exception{

};

/*! A requirements tree node
  This class implements a tree of requirements.
  Each tree node represents one requirement with a
  title and a rich-text description.

  Furthermore it can contain several attributes,
  links of user-defineable types to other requirements
  and several risk assessments.
 */
class Requirement
{
public:

    enum Type{
        UserRequirement,
        FunctionalRequirement,
        DesignRequirement,
        Section,
        TableRow
    };

    Requirement(UniqueIDManager *idManager,
                RequirementRefCounter *refCounter,
                shared_ptr<RiskAssessmentModel> riskAssessment,
                AttributeContainer *attributes, LinkContainer *links,
                AppSettings *settings);
    Requirement(UniqueIDManager *idManager,
                RequirementRefCounter *refCounter,
                shared_ptr<RiskAssessmentModel> riskAssessment,
                AttributeContainer *attributes, LinkContainer *links,
                AppSettings *settings, unsigned int proposedID);
    virtual ~Requirement();

    virtual uint getID();
    virtual bool isReference();

    virtual void setType(Type type);
    virtual Type getType() const;

    virtual void setParent(Requirement *parent);
    virtual Requirement* getParent();

    virtual QString number() const;
    virtual void setTitle(const QString &title);
    virtual QString getTitle() const;

    /*! Returns the requirement with its number
    - Requirements in the topmost level receive simple number
    - Requirements in deeper levels have numbers of the form "2.3.4"
    - For Design Requirements the number starts with "DS."


    \return QString containing the numbered requirement title
     */
    virtual QString getNumberedTitle() const;
    virtual QVariant getAttribute(int index) const;
    virtual void setAttribute(int index, const QVariant &value);

    virtual QTextDocument* getDescription();
    virtual shared_ptr<RiskAssessmentModel> getRiskAssessment();

    AttributeContainer *getAttributeContainer() const;

    virtual LinkContainer* getLinkContainer();
    virtual void addRequirementLink(int groupIdx, uint reqID);

    virtual int getRow() const;

    virtual Requirement *getChild(int index);

    virtual int childCount() const;
    virtual void insertChild(int beforeIndex, Requirement *child);
    virtual void appendChild(Requirement *child);

    virtual void removeChild(int index);
    virtual Requirement* popChild(int index);

    virtual int indexOf(const Requirement *item) const;
    virtual int displayIndexOf(const Requirement *item) const;

    static QString typeToString(Type type);
    static Type stringToType(const QString &typeString);

    QList<Requirement*> getReferenceList();

protected:
    const unsigned int id;

    Type type;
    UniqueIDManager *idManager;
    RequirementRefCounter *refCounter;
    Requirement *parent;
    QVector<Requirement*> children;

    QString title;
    QTextDocument *description;
    AttributeContainer *attributes;
    LinkContainer *links;
    AppSettings *settings;

    shared_ptr<RiskAssessmentModel> riskAssessment;


    void assertValidIndex(int index);
    void initialize(UniqueIDManager *idManager, RequirementRefCounter *refCounter,
                    shared_ptr<RiskAssessmentModel> riskAssessment,
                    AttributeContainer *attributes,
                    LinkContainer *links,
                    AppSettings *settings);
    bool sameTypeGroup(Type a, Type b) const;
};

#endif // REQUIREMENT_H
