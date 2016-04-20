#ifndef HTMLREPORTGENERATOR_H
#define HTMLREPORTGENERATOR_H

#include "htmltemplatefactory.h"
#include "htmltemplate.h"
#include "reportgenerator.h"
#include "requirementsmodel.h"
#include <QTextStream>

class HtmlReportGenerator : public ReportGenerator
{
public:
    HtmlReportGenerator(HtmlTemplateFactory *templateFactory);
    virtual ~HtmlReportGenerator();

    virtual void setModel(RequirementsModel *model);
    virtual void generate(const QString &filePath);

private:
    QFile file;
    QTextStream out;
    RequirementsModel *model;

    HtmlTemplateFactory *templateFactory;
    HtmlTemplate *documentTemplate;
    HtmlTemplate *srsTemplate;
    HtmlTemplate *frsTemplate;

    void initializeTemplates();
    QString generateHtml();
    QString generateSRS();
    QString generateFRS();
};

#endif // HTMLREPORTGENERATOR_H
