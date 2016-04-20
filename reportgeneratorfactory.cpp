#include "reportgeneratorfactory.h"
#include "htmlreportgenerator.h"

ReportGeneratorFactory::ReportGeneratorFactory(FileStateTracker *fileState)
{
    this->fileState = fileState;
}

ReportGeneratorFactory::~ReportGeneratorFactory()
{

}

ReportGenerator *ReportGeneratorFactory::newGenerator(const QString &type)
{
    if(type == "html")
        return newHtmlReportGenerator();
    else
        throw runtime_error("ReportGeneratorFactory: unkown generator type requested.");
}

ReportGenerator *ReportGeneratorFactory::newHtmlReportGenerator()
{
    return new HtmlReportGenerator(new HtmlTemplateFactory(),
                                   new TextDocumentSerializer(new RichTextResourceManager(fileState)));
}

