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
                xml->readNext();
                if(xml->isCDATA()){
                    QString characters = xml->text().toString();
                    model->getDescription(itemIdx)->setHtml(characters);
                }
            }
        }

        xml->readNext();
    }
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
