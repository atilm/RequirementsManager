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

    void initializeTemplates();
    QString generateHtml();
    QString generateSRS();
    QString generateFRS();
    QString buildSRSString(const QModelIndex &index);
    QString buildFRSString(const QModelIndex &index);
    QString idString(const QString &s);
    QString refString(QString s);
};

#endif // HTMLREPORTGENERATOR_H
