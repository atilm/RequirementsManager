#ifndef PROJECTFILEREADER_H
#define PROJECTFILEREADER_H

#include "requirementsmodel.h"
#include "qfileadapter.h"
#include <QXmlStreamReader>
#include <stdexcept>

class ParsingError : public runtime_error{
public:
    ParsingError(const string &arg) : runtime_error(arg) {}
};

class ProjectFileReader
{
public:
    ProjectFileReader(QXmlStreamReader *xml);
    virtual ~ProjectFileReader();

    virtual void load(RequirementsModel *model, QFileAdapter *file);

private:
    QXmlStreamReader *xml;
    QFileAdapter *file;
    RequirementsModel *model;
    AttributeContext *attributeContext;
    LinkContext *linkContext;

    void readContents();
    void parseAttributeDeclaration();
    void parseLinkDeclaration();
    void parseRequirement(QModelIndex parent);
    void parseDescription(QModelIndex itemIdx);
    void parseRequirementAttribute(QModelIndex itemIdx);
    void parseRequirementsLink(QModelIndex itemIdx);
    void parseRiskAssessment(QModelIndex itemIdx);
    void parseRiskScenario(RiskAssessment *ra);
    void parsePreventiveAction(RiskAssessment *ra);
    void storeAttributeValue(const QModelIndex &itemIdx,
                             int attributeIndex,
                             const QString &valueString);
    Qt::CheckState toCheckState(const QString &s);
    QString getAttribute(const QString &name);
    QString parseCharacters();
};

#endif // PROJECTFILEREADER_H
