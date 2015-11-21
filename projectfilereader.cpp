#include "projectfilereader.h"
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

void ProjectFileReader::load(RequirementsModel *model, QFileAdapter *file)
{
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        throw runtime_error(QObject::tr("Cannot open file.").toStdString());

    this->file = file;
    this->model = model;
    this->attributeContext = model->getAttributeContext();

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
            if(xml->name() == "AttributeDeclaration"){
                parseAttributeDeclaration();
            }
            else if(xml->name() == "Requirement"){
                parseRequirement(QModelIndex());
            }
            else
                continue;
        }
    }

    if(xml->hasError())
        throw runtime_error(xml->errorString().toStdString());

    xml->clear();
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

void ProjectFileReader::parseRiskAssessment(QModelIndex itemIdx)
{
    RiskAssessmentModel *riskModel = model->getRiskAssessment(itemIdx);
    riskModel->add(riskModel->index(riskModel->rowCount(),0));
    RiskAssessment *ra = riskModel->getRiskAssessment(riskModel->index(riskModel->rowCount()-1, 0));

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
