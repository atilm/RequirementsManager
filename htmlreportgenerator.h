#ifndef HTMLREPORTGENERATOR_H
#define HTMLREPORTGENERATOR_H

#include "htmltemplatefactory.h"
#include "htmltemplate.h"
#include "reportgenerator.h"
#include "requirementsmodel.h"
#include "textdocumentserializer.h"
#include <QTextStream>

class HtmlReportGenerator : public ReportGenerator
{
public:
    HtmlReportGenerator(HtmlTemplateFactory *templateFactory,
                        TextDocumentSerializer *documentSerializer);
    virtual ~HtmlReportGenerator();

    virtual void setModel(RequirementsModel *model);
    virtual void generate(const QString &filePath);

private:
    QFile file;
    QTextStream out;
    RequirementsModel *model;
    TextDocumentSerializer *documentSerializer;

    HtmlTemplateFactory *templateFactory;
    HtmlTemplate *documentTemplate;
    HtmlTemplate *srsTemplate;
    HtmlTemplate *frsTemplate;
    HtmlTemplate *dsTemplate;
    HtmlTemplate *requirementTemplate;
    HtmlTemplate *raTemplate;
    HtmlTemplate *tpTemplate;

    void initializeTemplates();
    QString generateHtml();
    QString generateSRS(const QModelIndex &index);
    QString generateFRS(const QModelIndex &index);
    QString generateDS(const QModelIndex &index);
    QString generateRA(const QModelIndex &index);
    QString generateTP(const QModelIndex &index);

    QString buildSRSString(const QModelIndex &index);
    QString buildFRSString(const QModelIndex &index);
    QString buildDSString(const QModelIndex &index);
    QString buildRASection(const QModelIndex &index);
    QString getRARows(Requirement* req);
    QString buildTPSection(const QModelIndex &index);
    QString getTPRows(Requirement *req);
    QString getTestPlan(RiskAssessment *ra, const QString &raNumber);

    QString getRepeatedRequirementRow(Requirement *req, const QString &section, int colSpan);
    QString idString(const QString &s, const QString &section);
    QString refString(const QString &s, const QString &section);
    QString underscored(QString s);
    QString constructRANumber(const QString &reqNumber, int raModelIndex);
    QString constructTestNumber(const QString &raNumber, int testModelIndex);
    bool isUserRequirement(const QModelIndex &index);
    bool isDesignSpecification(const QModelIndex &index);
    bool isUserOrFunctionalRequirement(const QModelIndex &index);
};

#endif // HTMLREPORTGENERATOR_H
