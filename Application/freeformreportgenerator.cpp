#include "freeformreportgenerator.h"

FreeFormReportGenerator::
FreeFormReportGenerator(shared_ptr<HtmlTemplateFactory> templateFactory,
                        shared_ptr<TextDocumentSerializer> documentSerializer,
                        shared_ptr<HtmlGenerator> htmlGenerator)
{
    this->templateFactory = templateFactory;
    this->documentSerializer = documentSerializer;
    this->htmlGenerator = htmlGenerator;
}

FreeFormReportGenerator::~FreeFormReportGenerator()
{
}

QString FreeFormReportGenerator::getTypeString()
{
    return "Free Form Html";
}

QString FreeFormReportGenerator::getDescription()
{
    return "Generates a freely structured html report.";
}

void FreeFormReportGenerator::setModel(shared_ptr<RequirementsModel> model)
{
    this->model = model;
}

void FreeFormReportGenerator::generate(const QString &filePath)
{

}
