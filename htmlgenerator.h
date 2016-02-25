#ifndef HTMLGENERATOR_H
#define HTMLGENERATOR_H

#include "riskassessment.h"
#include "preventiveaction.h"
#include "testnode.h"
#include "htmltemplatefactory.h"
#include <QString>

class HtmlGenerator
{
public:
    enum HeaderType{
        NO_HEADER,
        FIRST_LINE
    };

    HtmlGenerator(HtmlTemplateFactory *_templateFactory);
    virtual ~HtmlGenerator();

    void initTemplates(QString riskPath,
                       QString actionPath);

    QString toHtml(const TestNode &test);
    QString toHtml(const PreventiveAction &s);
    QString toHtml(const RiskAssessment &risk);
    QString htmlReplacements(QString s);
    QString toHtml(const QString &markupText, HeaderType headingType = NO_HEADER);

private:
    HtmlTemplateFactory *templateFactory;
    HtmlTemplate *actionTemplate;
    HtmlTemplate *riskAssessmentTemplate;
};

#endif // HTMLGENERATOR_H
