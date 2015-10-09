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

    this->file = file;
    this->model = model;
    this->attributeContext = model->getAttributeContext();

    xml->setDevice(file);
    xml->setAutoFormatting(true);
    xml->writeStartDocument();
    xml->writeStartElement("RequirementSpecification");
    xml->writeAttribute("version", "1.0");

    writeAttributeContext();
    writeRequirementSpecification();

    xml->writeEndElement(); // RequirementSpecification
    xml->writeEndDocument();

    this->file->close();
    this->model = NULL;
    this->file = NULL;
}

void ProjectFileWriter::writeAttributeContext()
{
    xml->writeStartElement("AttributeContext");

    for(int a=0;a < attributeContext->rowCount();a++)
        writeAttributeDeclaration(a);

    xml->writeEndElement(); // AttributeContext
}

void ProjectFileWriter::writeAttributeDeclaration(int index)
{
    xml->writeStartElement("AttributeDeclaration");
    xml->writeAttribute("index", QString("%1").arg(index));
    xml->writeAttribute("name", attributeContext->name(index));
    xml->writeAttribute("type", attributeContext->typeString(index));
    xml->writeEndElement(); // Attribute
}

void ProjectFileWriter::writeRequirementSpecification()
{
    xml->writeStartElement("RequirementSpecification");
    writeChildrenOf(QModelIndex());
    xml->writeEndElement();
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
    QString id = QString("%1").arg(model->getID(itemIdx));
    QString type = Requirement::typeToString(model->getType(itemIdx));
    QTextDocument *description = model->getDescription(itemIdx);

    xml->writeAttribute("id", id);
    xml->writeAttribute("type", type);
    xml->writeAttribute("name", title);

    xml->writeStartElement("description");
    xml->writeCDATA(description->toHtml());
    xml->writeEndElement(); // description

    for(int a=0;a < attributeContext->rowCount();a++)
        writeAttribute(parent, row, a);

    writeChildrenOf(itemIdx);

    xml->writeEndElement(); // Requirement
}

void ProjectFileWriter::writeAttribute(const QModelIndex &parent, int row, int attributeIndex)
{
    QString value = getAttributeValue(parent, row, attributeIndex);

    xml->writeStartElement("Attribute");
    xml->writeAttribute("index", QString("%1").arg(attributeIndex));
    xml->writeAttribute("value", value);
    xml->writeEndElement();
}

QString ProjectFileWriter::getAttributeValue(const QModelIndex &parent, int row, int attributeIndex)
{
    QModelIndex itemIdx = model->index(row, attributeIndex+1, parent);

    switch(attributeContext->type(attributeIndex)){
    case AttributeContext::BOOLEAN:
        return checkStateToString(model->data(itemIdx, Qt::CheckStateRole));
    case AttributeContext::TEXT:
        return model->data(itemIdx, Qt::DisplayRole).toString();
    }
}

QString ProjectFileWriter::checkStateToString(const QVariant &value)
{
    switch(value.toInt()){
    case Qt::Checked:
        return "yes";
    case Qt::Unchecked:
        return "no";
    default:
        return "";
    }
}

