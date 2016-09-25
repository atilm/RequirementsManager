#ifndef FREEFORMREPORTGENERATOR_H
#define FREEFORMREPORTGENERATOR_H

#include <memory>

#include "htmlgenerator.h"
#include "reportgenerator.h"
#include "textdocumentserializer.h"

using namespace std;

class FreeFormReportGenerator : public ReportGenerator
{
public:
    FreeFormReportGenerator(shared_ptr<HtmlTemplateFactory> templateFactory,
                            shared_ptr<TextDocumentSerializer> documentSerializer,
                            shared_ptr<HtmlGenerator> htmlGenerator);
    virtual ~FreeFormReportGenerator();

    virtual QString getTypeString();
    virtual QString getDescription();
    virtual void setModel(shared_ptr<RequirementsModel> model);
    virtual void generate(const QString &filePath);

private:
    shared_ptr<HtmlTemplateFactory> templateFactory;
    shared_ptr<TextDocumentSerializer> documentSerializer;
    shared_ptr<HtmlGenerator> htmlGenerator;
    shared_ptr<RequirementsModel> model;
};

#endif // FREEFORMREPORTGENERATOR_H
