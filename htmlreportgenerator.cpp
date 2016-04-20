#include "htmlreportgenerator.h"

HtmlReportGenerator::HtmlReportGenerator(HtmlTemplateFactory *templateFactory,
                                         TextDocumentSerializer *documentSerializer)
{
    model = nullptr;
    this->templateFactory = templateFactory;
    this->documentSerializer = documentSerializer;

    initializeTemplates();
}

HtmlReportGenerator::~HtmlReportGenerator()
{
    delete templateFactory;
    delete documentSerializer;
}

void HtmlReportGenerator::setModel(RequirementsModel *model)
{
    this->model = model;
}

void HtmlReportGenerator::generate(const QString &filePath)
{
    file.setFileName(filePath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        out.setDevice(&file);

        out << generateHtml();
    }
    file.close();
}

void HtmlReportGenerator::initializeTemplates()
{
    documentTemplate = templateFactory->newTemplate();
    srsTemplate = templateFactory->newTemplate();
    frsTemplate = templateFactory->newTemplate();

    documentTemplate->initialize("./Templates/ValidationDocumentTemplate.html");
    srsTemplate->initialize("./Templates/srsLineTemplate.html");
    frsTemplate->initialize("./Templates/frsLineTemplate.html");
}

QString HtmlReportGenerator::generateHtml()
{
    documentTemplate->setField("SRS", generateSRS());
    documentTemplate->setField("FRS", generateFRS());
    return documentTemplate->getHtml();
}

QString HtmlReportGenerator::generateSRS()
{
    QString lines;

    for(int i=0;i < model->rowCount();i++){
        Requirement *req = model->getRequirement(model->index(i, 0));

        srsTemplate->setField("NUMBER", req->number());
        srsTemplate->setField("HREF", req->number().replace(".","_"));
        srsTemplate->setField("NAME", req->getTitle());
        QString description = documentSerializer->toSimpleHtml(req->getDescription());
        srsTemplate->setField("DESC", description);

        lines.append(srsTemplate->getHtml());
    }

    return lines;
}

QString HtmlReportGenerator::generateFRS()
{
    return QString();
}

