#ifndef PROJECTFILEWRITER_H
#define PROJECTFILEWRITER_H

#include "requirementsmodel.h"
#include "riskassessmentmodel.h"
#include "preventiveactionmodel.h"
#include "qfileadapter.h"
#include "textdocumentserializer.h"
#include "richtextresourcemanager.h"
#include <QString>
#include <QXmlStreamWriter>

#include <memory>
using namespace std;

class ProjectFileController;

class ProjectFileWriter
{
public:
    ProjectFileWriter(QXmlStreamWriter *xml,
                      TextDocumentSerializer *serializer,
                      RichTextResourceManager *resourceManger);
    virtual ~ProjectFileWriter();

    virtual void save(ProjectFileController *fileController, QFileAdapter *file);

private:
    QXmlStreamWriter *xml;
    TextDocumentSerializer *serializer;
    ProjectFileController *fileController;
    shared_ptr<RequirementsModel> model;
    AttributeContext *attributeContext;
    LinkContext *linkContext;
    QFileAdapter *file;
    RichTextResourceManager *resourceManger;

    void writeProgrammingLanguage();
    void writeSourceDirectories();
    void writeTestDirectories();
    void writeAttributeContext();
    void writeAttributeDeclaration(int index);
    void writeLinkContext();
    void writeLinkGroupDeclaration(int index);
    void writeRequirementSpecification();
    void writeChildrenOf(QModelIndex parent);
    void writeRequirement(int row, QModelIndex &parent);
    void writeReqReferenceContent(const QModelIndex &index, RequirementReference *reqRef);
    void writeReferenceContent(const QModelIndex &index, Requirement *requirement);
    void writeRequirementContent(const QModelIndex &index, Requirement *requirement);
    void write_ID_and_Type(const QModelIndex &itemIdx);
    void writeAttribute(const QModelIndex &parent, int row, int attributeIndex);
    void writeLinks(const QModelIndex &itemIdx);
    void writeRiskAssessmentModel(shared_ptr<RiskAssessmentModel> risks);
    void writeRiskAssessment(shared_ptr<RiskAssessment> risk);
    void writePreventiveActions(shared_ptr<PreventiveActionModel> actions);
    void writePreventiveAction(shared_ptr<PreventiveAction> action);
    void writeTestReference(shared_ptr<PreventiveAction> action);
    void writePreventiveActionContent(shared_ptr<PreventiveAction> action);

    QString getAttributeValue(const QModelIndex &parent, int row, int attributeIndex);
    QString checkStateToString(const QVariant &value);
    QString intToString(int n);
};

#endif // PROJECTFILEWRITER_H
