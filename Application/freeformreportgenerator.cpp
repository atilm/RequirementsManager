#include <QDebug>

#include "freeformreportgenerator.h"
#include "requirementsmodeliterator.h"

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

//    if(index.isValid()){
//        Requirement *requirement = model->getRequirement(index);

//        if(requirement->getType() == Requirement::Section){
//            lines.append(buildSectionString(requirement, depth));
//        }
//        else if(requirement->getType() == Requirement::TableRow){
//            lines.append(buildTableString(index));
//        }
//    }

//    for(int i = 0; i < model->rowCount(index); i++){
//        QModelIndex childIndex = model->index(i, 0, index);
//        lines.append(generateContent(childIndex, depth + 1));
//    }

    RequirementsModelIterator it(model);

    lines.append("<table>\r\n");
    do
    {
        Requirement *req = it.currentRequirement();

        if(req){
            lines.append(QString("<tr><td>%1</td>\r\n"
                                 "<td>%2</td></tr>\r\n")
                         .arg(it.getCurrentDepth())
                         .arg(req->getNumberedTitle()));
        }
    }
    while(it.next());

    lines.append("</table>\r\n");

    return lines;
}

QString FreeFormReportGenerator::buildSectionString(Requirement *requirement,
                                                    uint depth)
{
    QString temp = "<h%1>%2 [%3] %4</h%1>\r\n"
                   "<p>%3</p>\r\n";

    return temp
            .arg(depth)
            .arg(requirement->number())
            .arg(requirement->getID(), 3, 10, QChar('0'))
            .arg(requirement->getTitle())
            .arg(documentSerializer->toSimpleHtml(requirement->getDescription()));
}

QString FreeFormReportGenerator::buildTableString(const QModelIndex &index)
{
//    QModelIndex parentIdx = index.parent();
//    Requirement *parent = model->getRequirement(parentIdx);

    QString lines;
//    for(int row = currentIdx.row(); row < parent->childCount(); row++){

//        QModelIndex currentIdx = model->index(row, 0, parentIdx);
//        Requirement *currentReq = model->getRequirement(currentIdx);

//        if(currentReq->getType() != Requirement::TableRow){
//            break;
//        }

//        lines.append(buildTableRow(model->getRequirement(currentIdx)));

//        row++;
//        currentReq = model->getRequirement(index);

//    }

    return lines;
}



QString FreeFormReportGenerator::buildTableRow(Requirement *requirement)
{
    return QString();
}

