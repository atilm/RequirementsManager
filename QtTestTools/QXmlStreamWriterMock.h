#ifndef QXMLSTREAMWRITERMOCK_H
#define QXMLSTREAMWRITERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "qxmlstreamwriteradapter.h"

class QXmlStreamWriterAdapterMock : public QXmlStreamWriterAdapter {
public:

    MOCK_METHOD1(setAutoFormatting, void (bool enable));
    MOCK_METHOD1(setDevice, void (QIODevice *device));
    MOCK_METHOD0(writeStartDocument, void ());
    MOCK_METHOD1(writeStartElement, void (const QString &qualifiedName));
    MOCK_METHOD2(writeAttribute, void (const QString &qualifiedName, const QString &value));
    MOCK_METHOD2(writeTextElement, void (const QString &qualifiedName, const QString &value));
    MOCK_METHOD0(writeEndElement, void ());
    MOCK_METHOD0(writeEndDocument, void ());
};

#endif // QXMLSTREAMWRITERMOCK_H
