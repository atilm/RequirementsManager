#ifndef QXMLSTREAMWRITERADAPTER_H
#define QXMLSTREAMWRITERADAPTER_H

#include <QXmlStreamWriter>

class QXmlStreamWriterAdapter : public QXmlStreamWriter
{
public:
    QXmlStreamWriterAdapter();
    virtual ~QXmlStreamWriterAdapter();

    virtual void setAutoFormatting(bool enable);
    virtual void setDevice(QIODevice *device);
    virtual void writeStartDocument();
    virtual void writeStartElement(const QString &qualifiedName);
    virtual void writeAttribute(const QString &qualifiedName, const QString &value);
    virtual void writeTextElement(const QString &qualifiedName, const QString &value);
    virtual void writeEndElement();
    virtual void writeEndDocument();
};

#endif // QXMLSTREAMWRITERADAPTER_H
