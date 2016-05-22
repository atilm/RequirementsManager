#include "qtextstreamadapter.h"

QTextStreamAdapter::QTextStreamAdapter()
{
    stream = new QTextStream();
}

QTextStreamAdapter::~QTextStreamAdapter()
{
    delete stream;
}

bool QTextStreamAdapter::atEnd() const
{
    return stream->atEnd();
}

QString QTextStreamAdapter::readLine()
{
    return stream->readLine();
}

QString QTextStreamAdapter::readAll()
{
    return stream->readAll();
}

void QTextStreamAdapter::setDevice(QFileAdapter *device)
{
    stream->setDevice(device);
}

void QTextStreamAdapter::write(const QString &string)
{
    *stream << string;
}

