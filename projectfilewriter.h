#ifndef PROJECTFILEWRITER_H
#define PROJECTFILEWRITER_H

#include "requirementsmodel.h"
#include "riskassessmentmodel.h"
#include "preventiveactionmodel.h"
#include "qfileadapter.h"
#include <QString>
#include <QXmlStreamWriter>

class ProjectFileController;

class ProjectFileWriter
{
public:
    ProjectFileWriter(QXmlStreamWriter *xml);
    virtual ~ProjectFileWriter();

    virtual void save(ProjectFileController *fileController, QFileAdapter *file);

private:
    QXmlStreamWriter *xml;
    ProjectFileController *fileController;
    RequirementsModel *model;
    AttributeContext *attributeContext;
    LinkContext *linkContext;
    QFileAdapter *file;

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
    void writeReferenceContent(const QModelIndex &index, Requirement *requirement);
    void writeRequirementContent(const QModelIndex &index, Requirement *requirement);
    void write_ID_and_Type(const QModelIndex &itemIdx);
    void writeAttribute(const QModelIndex &parent, int row, int attributeIndex);
    void writeLinks(const QModelIndex &itemIdx);
    void writeRiskAssessmentModel(RiskAssessmentModel *risks);
    void writeRiskAssessment(RiskAssessment *risk);
    void writePreventiveActions(PreventiveActionModel *actions);
    void writePreventiveAction(PreventiveAction *action);
    void writeTestReference(PreventiveAction *action);
    void writePreventiveActionContent(PreventiveAction *action);

    QString getAttributeValue(const QModelIndex &parent, int row, int attributeIndex);
    QString checkStateToString(const QVariant &value);
    QString intToString(int n);
};

#endif // PROJECTFILEWRITER_H
