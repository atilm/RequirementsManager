#include "freeformreportgenerator.h"

FreeFormReportGenerator::
FreeFormReportGenerator(shared_ptr<HtmlTemplateFactory> templateFactory,
                        shared_ptr<TextDocumentSerializer> documentSerializer,
                        shared_ptr<HtmlGenerator> htmlGenerator)
{
    this->templateFactory = templateFactory;
    this->documentSerializer = documentSerializer;
    this->htmlGenerator = htmlGenerator;

    initializeTemplates();
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
    file.setFileName(filePath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        out.setDevice(&file);
        out << generateHtml();
    }
    file.close();
}

void FreeFormReportGenerator::initializeTemplates()
{
    documentTemplate = templateFactory->newTemplate();

    documentTemplate->initialize("./Templates/FreeForm/DocumentTemplate.html");
}

QString FreeFormReportGenerator::generateHtml()
{
    documentTemplate->setField("TITLE", "Software Specification");
    documentTemplate->setField("CONTENT", generateContent(QModelIndex(), 1));

    return documentTemplate->getHtml();
}

QString FreeFormReportGenerator::generateContent(const QModelIndex &index,
                                                 uint depth)
{
    QString lines;

    if(index.isValid()){
        Requirement *requirement = model->getRequirement(index);

        if(requirement->getType() == Requirement::Section){
            lines.append(buildSectionString(requirement, depth));
        }
    }

    for(int i = 0; i < model->rowCount(index); i++){
        QModelIndex childIndex = model->index(i, 0, index);
        lines.append(generateContent(childIndex, depth + 1));
    }

    return lines;
}

QString FreeFormReportGenerator::buildSectionString(Requirement *requirement,
                                                    uint depth)
{
    QString temp = "<h%1>%2</h%1>\r\n"
                   "<p>%3</p>\r\n";

    return temp
            .arg(depth)
            .arg(requirement->getNumberedTitle())
            .arg(documentSerializer->toSimpleHtml(requirement->getDescription()));
}
