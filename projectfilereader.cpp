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
            if(xml->name() == "Requirement"){

                model->appendChild(QModelIndex());
                int rowIdx = model->rowCount() - 1;
                QModelIndex newIdx = model->index(rowIdx, 0, QModelIndex());

                parseRequirement(newIdx);
            }
            else
                continue;
        }
    }

    if(xml->hasError())
        throw runtime_error(xml->errorString().toStdString());

    xml->clear();
}

void ProjectFileReader::parseRequirement(QModelIndex item)
{
    QString title = getAttribute("name");
    model->setData(item, title);

    xml->readNext();

    while(!(xml->tokenType() == QXmlStreamReader::EndElement &&
            xml->name() == "Requirement")){

        if(xml->tokenType() == QXmlStreamReader::StartElement){
            if(xml->name() == "Requirement"){

                model->appendChild(item);
                int rowIdx = model->rowCount(item) - 1;
                QModelIndex newIdx = model->index(rowIdx, 0, item);

                parseRequirement(newIdx);
            }
            else if(xml->name() == "description"){
                xml->readNext();
                if(xml->isCDATA()){
                    QString characters = xml->text().toString();
                    model->getDescription(item)->setHtml(characters);
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
