#include <memory>

#include <QDebug>

#include "freeformreportgenerator.h"
#include "requirementsmodeliterator.h"

using namespace std;

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
    delete documentTemplate;
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

    QString content = generateContent();

    documentTemplate->setField("CONTENT", content);

    return documentTemplate->getHtml();
}

QString FreeFormReportGenerator::generateContent()
{
    contentLines.clear();
    currentType = Requirement::Section;

    buildCustomPart();

    buildDesignSpecification();

    return contentLines.join("\r\n");
}

void FreeFormReportGenerator::buildCustomPart()
{
    modelIterator = make_shared<RequirementsModelIterator>(model);

    buildLinesForCurrentItem();

    while(modelIterator->next()){
        buildLinesForCurrentItem();
    }

    closeTableAtEnd();
}

void FreeFormReportGenerator::buildDesignSpecification()
{
    contentLines.append("<h2>Design Specification</h2>");
    contentLines.append("<table>");
    contentLines.append("<tr>"
                        "<th>No.</th>"
                        "<th>ID</th>"
                        "<th>Title</th>"
                        "<th>Description</th>"
                        "</tr>");

    modelIterator->toBegin();

    buildCurrentDesignSpecItem();

    while(modelIterator->next()){
        buildCurrentDesignSpecItem();
    }

    contentLines.append("</table>");
}

void FreeFormReportGenerator::buildLinesForCurrentItem()
{
    Requirement *requirement = modelIterator->currentRequirement();

    // We deal with design specification in a second pass through
    // the whole specification:
    if(requirement->getType() == Requirement::DesignRequirement){
        return;
    }

    openOrCloseTables(requirement);

    if(requirement->getType() == Requirement::Section){
        contentLines.append(buildSectionString(requirement));
    }
    else if(requirement->getType() == Requirement::TableRow){
        contentLines.append(buildTableString(requirement));
    }
    else if(isUserOrFunctionalRequirement(requirement)){
        contentLines.append(buildRequirementString(requirement));
    }
}

void FreeFormReportGenerator::buildCurrentDesignSpecItem()
{
    Requirement *requirement = modelIterator->currentRequirement();

    if(isUserOrFunctionalRequirement(requirement)){
        contentLines.append(buildRequirementString(requirement, false));
    }
    else if(requirement->getType() == Requirement::DesignRequirement){
        contentLines.append(buildRequirementString(requirement));
    }
}

bool FreeFormReportGenerator::isUserOrFunctionalRequirement(Requirement *requirement)
{
    return isUserOrFunctionalRequirement(requirement->getType());
}

bool FreeFormReportGenerator::isUserOrFunctionalRequirement(Requirement::Type type)
{
    return ( type == Requirement::UserRequirement ||
             type == Requirement::FunctionalRequirement ) ;
}

void FreeFormReportGenerator::openOrCloseTables(Requirement *requirement)
{
    Requirement::Type nextType = requirement->getType();

    if(typeChanged(currentType, nextType)){
        closeCurrentTable(currentType);
        openNextTable(nextType);
    }

    currentType = nextType;
}

bool FreeFormReportGenerator::typeChanged(Requirement::Type current,
                                          Requirement::Type next)
{
    if(current == next){
        return false;
    }
    else{
        if( isUserOrFunctionalRequirement(current) &&
            isUserOrFunctionalRequirement(next) )
        {
            return false;
        }
        else{
            return true;
        }
    }
}

void FreeFormReportGenerator::closeCurrentTable(Requirement::Type type)
{
    switch(type){
    case Requirement::Section:
        break;
    case Requirement::UserRequirement:
        contentLines.append("</table>");
        break;
    case Requirement::FunctionalRequirement:
        contentLines.append("</table>");
        break;
    case Requirement::DesignRequirement:
        contentLines.append("</table>");
        break;
    case Requirement::TableRow:
        contentLines.append("</table>");
        break;
    }
}

void FreeFormReportGenerator::closeTableAtEnd()
{
    closeCurrentTable(currentType);
}

void FreeFormReportGenerator::openNextTable(Requirement::Type type)
{
    switch(type){
    case Requirement::Section:
        break;
    case Requirement::UserRequirement:
        contentLines.append("<table>");
        contentLines.append("<tr>"
                            "<th>No.</th>"
                            "<th>ID</th>"
                            "<th>Title</th>"
                            "<th>Description</th>"
                            "</tr>");
        break;
    case Requirement::FunctionalRequirement:
        break;
    case Requirement::DesignRequirement:
        break;
    case Requirement::TableRow:
        contentLines.append("<table>");
        contentLines.append("<tr>"
                            "<th>No.</th>"
                            "<th>Description</th>"
                            "</tr>");
        break;
    }
}

QString FreeFormReportGenerator::buildSectionString(Requirement *requirement)
{
    QString temp = "<h%1>%2 %3</h%1>"
                   "<p>%4</p>";

    return temp
            .arg(modelIterator->getCurrentDepth() + 1)
            .arg(requirement->number())
            .arg(requirement->getTitle())
            .arg(documentSerializer->toSimpleHtml(requirement->getDescription()));
}

QString FreeFormReportGenerator::buildTableString(Requirement *requirement)
{
    QString tableRow = "<tr>"
                       "<td>%1</td>"
                       "<td><b>%2</b><p>%3</p></td>"
                       "</tr>";

    return tableRow.arg(requirement->number())
            .arg(requirement->getTitle())
            .arg(documentSerializer->toSimpleHtml(requirement->getDescription()));
}

QString FreeFormReportGenerator::buildRequirementString(Requirement *requirement,
                                                        bool showDescription)
{
    QString tableRow = "<tr>"
                       "<td>%1</td>"
                       "<td>[%2]</td>"
                       "<td>%3</td>"
                       "<td>%4</td>"
                       "</tr>";

    QString description = "see above";

    if(showDescription){
        description = documentSerializer->toSimpleHtml(requirement->getDescription());
    }

    return tableRow
            .arg(requirement->number())
            .arg(requirement->getID(), 3, 10, QChar('0'))
            .arg(requirement->getTitle())
            .arg(description);
}

