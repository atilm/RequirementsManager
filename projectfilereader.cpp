#include "projectfilereader.h"
#include "projectfilecontroller.h"
#include <stdexcept>
#include <iostream>
using namespace std;

ProjectFileReader::ProjectFileReader(QXmlStreamReader *xml)
{
    this->xml = xml;
}

ProjectFileReader::~ProjectFileReader()
{
    delete xml;
}

void ProjectFileReader::load(ProjectFileController *fileController, QFileAdapter *file)
{
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        throw runtime_error(QObject::tr("Cannot open file.").toStdString());

    this->file = file;
    this->fileController = fileController;
    this->model = fileController->getRequirementsModel();
    this->attributeContext = model->getAttributeContext();
    this->linkContext = model->getLinkContext();

    readContents();

    this->file->close();
    this->model = NULL;
    this->file = NULL;
}

void ProjectFileReader::readContents()
{
    xml->setDevice(file);

    while(!xml->atEnd() && !xml->hasError()){
        QXmlStreamReader::TokenType token = xml->readNext();

        if(token == QXmlStreamReader::StartElement){
            if(xml->name() == "Language")
                parseProgrammingLanguage();
            else if(xml->name() == "SourceDir")
                parseSourceDirectory();
            else if(xml->name() == "TestDir")
                parseTestDirectory();
            else if(xml->name() == "AttributeDeclaration")
                parseAttributeDeclaration();
            else if(xml->name() == "LinkDeclaration")
                parseLinkDeclaration();
            else if(xml->name() == "Requirement")
                parseRequirement(QModelIndex());
            else
                continue;
        }
    }

    if(xml->hasError())
        throw runtime_error(xml->errorString().toStdString());

    xml->clear();
}

void ProjectFileReader::parseProgrammingLanguage()
{
    xml->readNext();
    fileController->setProgrammingLanguage(xml->text().toString());
}

void ProjectFileReader::parseSourceDirectory()
{
    xml->readNext();
    QString dir = xml->text().toString();
    fileController->sourceDirModel()->add(dir);
}

void ProjectFileReader::parseTestDirectory()
{
    xml->readNext();
    QString dir = xml->text().toString();
    fileController->testDirModel()->add(dir);
}

void ProjectFileReader::parseAttributeDeclaration()
{
    uint index = getAttribute("index").toUInt();

    if(index != attributeContext->rowCount())
        throw ParsingError(QObject::tr("Unexpected index in attribute declaration.").toStdString());

    QString name = getAttribute("name");
    QString typeString = getAttribute("type");

    attributeContext->addAttribute(name, typeString);
}

void ProjectFileReader::parseLinkDeclaration()
{
    uint index = getAttribute("index").toUInt();

    if(index != linkContext->rowCount())
        throw ParsingError(QObject::tr("Unexpected index in link declaration.").toStdString());

    QString name = getAttribute("name");
    linkContext->addLinkType(name);
}

void ProjectFileReader::parseRequirement(QModelIndex parent)
{  
    uint id = getAttribute("id").toUInt();
    QString typeString = getAttribute("type");
    Requirement::Type type = Requirement::stringToType(typeString);
    QString title = getAttribute("name");

    model->appendChild(parent, title, type, id);

    int rowIdx = model->rowCount(parent) - 1;
    QModelIndex itemIdx = model->index(rowIdx, 0, parent);

    xml->readNext();

    while(!(xml->tokenType() == QXmlStreamReader::EndElement &&
            xml->name() == "Requirement")){

        if(xml->tokenType() == QXmlStreamReader::StartElement){
            if(xml->name() == "Requirement"){
                parseRequirement(itemIdx);
            }
            else if(xml->name() == "description"){
                parseDescription(itemIdx);
            }
            else if(xml->name() == "Attribute"){
                parseRequirementAttribute(itemIdx);
            }
            else if(xml->name() == "Link"){
                parseRequirementsLink(itemIdx);
            }
            else if(xml->name() == "RiskAssessment"){
                parseRiskAssessment(itemIdx);
            }
        }

        xml->readNext();
    }
}

void ProjectFileReader::parseDescription(QModelIndex itemIdx)
{
    xml->readNext();
    if(xml->isCDATA()){
        QString characters = xml->text().toString();
        model->getDescription(itemIdx)->setHtml(characters);
    }
}

void ProjectFileReader::parseRequirementAttribute(QModelIndex itemIdx)
{
    int index = getAttribute("index").toInt();
    QString valueString = getAttribute("value");

    storeAttributeValue(itemIdx, index, valueString);
}

void ProjectFileReader::parseRequirementsLink(QModelIndex itemIdx)
{
    int groupIndex = getAttribute("group").toInt();
    uint requirementID = getAttribute("id").toUInt();

    Requirement *requirement = model->getRequirement(itemIdx);
    requirement->addRequirementLink(groupIndex, requirementID);
}

void ProjectFileReader::parseRiskAssessment(QModelIndex itemIdx)
{
    RiskAssessmentModel *riskModel = model->getRiskAssessment(itemIdx);
    RiskAssessment *ra = riskModel->appendAssessment();

    int initialProbability = getAttribute("initialProbability").toInt();
    int initialDamage = getAttribute("initialDamage").toInt();
    ra->initialRiskModel()->setCurrentRisk(ra->initialRiskModel()->index(initialDamage, initialProbability));

    int finalProbability = getAttribute("finalProbability").toInt();
    int finalDamage = getAttribute("finalDamage").toInt();
    ra->finalRiskModel()->setCurrentRisk(ra->finalRiskModel()->index(finalDamage, finalProbability));

    xml->readNext();

    while(!(xml->tokenType() == QXmlStreamReader::EndElement &&
            xml->name() == "RiskAssessment")){

        if(xml->tokenType() == QXmlStreamReader::StartElement){
            if(xml->name() == "scenario"){
                parseRiskScenario(ra);
            }
            if(xml->name() == "mitigationStrategy"){
                parseMitigationStrategy(ra);
            }
            else if(xml->name() == "Action"){
                parsePreventiveAction(ra);
            }
        }

        xml->readNext();
    }
}

void ProjectFileReader::parseRiskScenario(RiskAssessment *ra)
{
    xml->readNext();
    if(xml->isCharacters()){
        QString characters = xml->text().toString();
        ra->setScenario(characters);
    }
}

void ProjectFileReader::parseMitigationStrategy(RiskAssessment *ra)
{
    xml->readNext();
    if(xml->isCharacters()){
        QString characters = xml->text().toString();
        ra->setMitigationStrategy(characters);
    }
}

void ProjectFileReader::parsePreventiveAction(RiskAssessment *ra)
{
    PreventiveActionModel *actionModel = ra->getPreventiveActions();
    PreventiveAction *action = actionModel->appendAction();

    action->setTestCase(getAttribute("case"));
    action->setTestName(getAttribute("name"));

    xml->readNext();

    while(!(xml->tokenType() == QXmlStreamReader::EndElement &&
            xml->name() == "Action")){

        if(xml->tokenType() == QXmlStreamReader::StartElement){
            if(xml->name() == "short")
                action->setShortDescription(parseCharacters());
            else if(xml->name() == "preparation")
                action->setPreparation(parseCharacters());
            else if(xml->name() == "action")
                action->setAction(parseCharacters());
            else if(xml->name() == "result")
                action->setExpectedResult(parseCharacters());
        }

        xml->readNext();
    }
}

void ProjectFileReader::storeAttributeValue(const QModelIndex &itemIdx,
                                            int attributeIndex,
                                            const QString &valueString)
{
    QModelIndex attributeItemIndex = model->index(itemIdx.row(),
                                                  attributeIndex+1,
                                                  itemIdx.parent());

    switch(attributeContext->type(attributeIndex)){
    case AttributeContext::BOOLEAN:
        model->setData(attributeItemIndex, toCheckState(valueString), Qt::CheckStateRole);
        break;
    case AttributeContext::TEXT:
        model->setData(attributeItemIndex, valueString, Qt::EditRole);
    }
}

Qt::CheckState ProjectFileReader::toCheckState(const QString &s)
{
    if(s == "yes")
        return Qt::Checked;
    else
        return Qt::Unchecked;
}

QString ProjectFileReader::getAttribute(const QString &name)
{
    QXmlStreamAttributes attributes = xml->attributes();

    QString s;

    if(attributes.hasAttribute(name))
        s = attributes.value(name).toString();
    else
        s = "";

    return s;
}

QString ProjectFileReader::parseCharacters()
{
    xml->readNext();
    if(xml->isCharacters())
        return xml->text().toString();
    else
        return QString();
}
