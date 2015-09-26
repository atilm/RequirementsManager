#include "projectfilewriter.h"
#include "requirementsmodel.h"
#include <stdexcept>
#include <QString>
#include <QObject>
using namespace std;

ProjectFileWriter::ProjectFileWriter(QXmlStreamWriter *xml)
{
    this->xml = xml;
}

ProjectFileWriter::~ProjectFileWriter()
{
    delete xml;
}

void ProjectFileWriter::save(RequirementsModel *model,
                             QFileAdapter *file)
{
    if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
        throw runtime_error(QObject::tr("Could not open file.").toStdString());

    this->model = model;
    this->file = file;

    xml->setDevice(file);
    xml->setAutoFormatting(true);
    xml->writeStartDocument();
    xml->writeStartElement("RequirementSpecification");
    xml->writeAttribute("version", "1.0");

    writeChildrenOf(QModelIndex());

    xml->writeEndElement(); // RequirementSpecification
    xml->writeEndDocument();

    this->file->close();
    this->model = NULL;
    this->file = NULL;
}

void ProjectFileWriter::writeChildrenOf(QModelIndex parent)
{
    int rowCount = model->rowCount(parent);
    for(int row=0;row < rowCount;row++){
        writeRequirement(row, parent);
    }
}

void ProjectFileWriter::writeRequirement(int row, QModelIndex parent)
{
    xml->writeStartElement("Requirement");

    QModelIndex itemIdx = model->index(row, 0, parent);
    QString title = model->data(itemIdx).toString();
    QTextDocument *description = model->getDescription(itemIdx);

    xml->writeAttribute("name", title);

    xml->writeStartElement("description");
    xml->writeCDATA(description->toHtml());
    xml->writeEndElement(); // description

    writeChildrenOf(itemIdx);

    xml->writeEndElement(); // Requirement
}

