#ifndef PROJECTFILEREADER_H
#define PROJECTFILEREADER_H

#include "requirementsmodel.h"
#include "qfileadapter.h"
#include "richtextresourcemanager.h"
#include <QXmlStreamReader>
#include <stdexcept>
#include <memory>
using namespace std;

class PreventiveActionFactory;
class ProjectFileController;

class ParsingError : public runtime_error{
public:
    ParsingError(const string &arg) : runtime_error(arg) {}
};

class ProjectFileReader
{
public:
    ProjectFileReader(QXmlStreamReader *xml,
                      RichTextResourceManager *resources);
    virtual ~ProjectFileReader();

    virtual void injectRequirementFactory(RequirementFactory *factory);
    virtual void injectPreventiveActionFacotry(shared_ptr<PreventiveActionFactory> actionFactory);
    virtual void load(ProjectFileController *fileController, QFileAdapter *file);

private:
    QXmlStreamReader *xml;
    RichTextResourceManager *resources;
    QFileAdapter *file;
    ProjectFileController *fileController;
    shared_ptr<RequirementsModel> model;
    AttributeContext *attributeContext;
    LinkContext *linkContext;
    RequirementFactory *factory;
    shared_ptr<PreventiveActionFactory> actionFactory;

    void readContents();
    void parseProgrammingLanguage();
    void parseSourceDirectory();
    void parseTestDirectory();
    void parseAttributeDeclaration();
    void parseLinkDeclaration();
    void parseRequirement(QModelIndex parent);
    void parseRequirementReference(QModelIndex parent);
    void parseDesignReference(QModelIndex parent);
    void parseRequirementContent(QModelIndex itemIdx, const QString &typeString);
    void parseDescription(QModelIndex itemIdx);
    void parseRequirementAttribute(QModelIndex itemIdx);
    void parseRequirementsLink(QModelIndex itemIdx);
    void parseRiskAssessment(QModelIndex itemIdx);
    void parseRiskScenario(shared_ptr<RiskAssessment> ra);
    void parseMitigationStrategy(shared_ptr<RiskAssessment> ra);
    void parsePreventiveAction(shared_ptr<RiskAssessment> ra);
    void parseTestReference(shared_ptr<RiskAssessment> ra);
    void storeAttributeValue(const QModelIndex &itemIdx,
                             int attributeIndex,
                             const QString &valueString);
    Qt::CheckState toCheckState(const QString &s);
    QString getAttribute(const QString &name);
    QString parseCharacters();
};

#endif // PROJECTFILEREADER_H
