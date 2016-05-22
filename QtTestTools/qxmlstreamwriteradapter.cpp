#include "qxmlstreamwriteradapter.h"

QXmlStreamWriterAdapter::QXmlStreamWriterAdapter()
{
}

QXmlStreamWriterAdapter::~QXmlStreamWriterAdapter()
{

}

void QXmlStreamWriterAdapter::setAutoFormatting(bool enable)
{
    QXmlStreamWriter::setAutoFormatting(enable);
}

void QXmlStreamWriterAdapter::setDevice(QIODevice *device)
{
    QXmlStreamWriter::setDevice(device);
}

void QXmlStreamWriterAdapter::writeStartDocument()
{
    QXmlStreamWriter::writeStartDocument();
}

void QXmlStreamWriterAdapter::writeStartElement(const QString &qualifiedName)
{
    QXmlStreamWriter::writeStartElement(qualifiedName);
}

void QXmlStreamWriterAdapter::writeAttribute(const QString &qualifiedName, const QString &value)
{
    QXmlStreamWriter::writeAttribute(qualifiedName, value);
}

void QXmlStreamWriterAdapter::writeTextElement(const QString &qualifiedName, const QString &value)
{
    QXmlStreamWriter::writeTextElement(qualifiedName, value);
}

void QXmlStreamWriterAdapter::writeEndElement()
{
    QXmlStreamWriter::writeEndElement();
}

void QXmlStreamWriterAdapter::writeEndDocument()
{
    QXmlStreamWriter::writeEndDocument();
}
