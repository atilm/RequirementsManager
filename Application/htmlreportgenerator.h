#ifndef HTMLREPORTGENERATOR_H
#define HTMLREPORTGENERATOR_H

#include "htmlgenerator.h"
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
                        TextDocumentSerializer *documentSerializer,
                        HtmlGenerator *html);
    virtual ~HtmlReportGenerator();

    virtual void setModel(shared_ptr<RequirementsModel> model);
    virtual void generate(const QString &filePath);

private:
    QFile file;
    QTextStream out;
    shared_ptr<RequirementsModel> model;
    TextDocumentSerializer *documentSerializer;
    HtmlGenerator *html;

    HtmlTemplateFactory *templateFactory;
    HtmlTemplate *documentTemplate;
    HtmlTemplate *srsTemplate;
    HtmlTemplate *frsTemplate;
    HtmlTemplate *dsTemplate;
    HtmlTemplate *sectionHeaderTemplate;
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
    QString getTestPlan(shared_ptr<RiskAssessment> ra, const QString &raNumber);

    QString sectionHeader(const QString &number, const QString &section, const QString &previousSection, int rowSpan, int colSpan, const QString &content);
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
