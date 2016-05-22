#include "qlocalsocketadapter.h"

QLocalSocketAdapter::QLocalSocketAdapter(QObject *parent) :
    QObject(parent)
{
    socket = new QLocalSocket(parent);

    connect(socket, SIGNAL(readyRead()), this, SIGNAL(readyRead()));
}

QLocalSocketAdapter::~QLocalSocketAdapter()
{
    delete socket;
}

void QLocalSocketAdapter::connectToServer(const QString &name, QIODevice::OpenMode openMode)
{
    socket->connectToServer(name, openMode);
}

void QLocalSocketAdapter::disconnectFromServer()
{
    socket->disconnectFromServer();
}

void QLocalSocketAdapter::close()
{
    socket->close();
}

bool QLocalSocketAdapter::isOpen() const
{
    return socket->isOpen();
}

bool QLocalSocketAdapter::waitForConnected(int msecs)
{
    return socket->waitForConnected(msecs);
}

bool QLocalSocketAdapter::waitForBytesWritten(int msecs)
{
    return socket->waitForBytesWritten(msecs);
}

QByteArray QLocalSocketAdapter::readAll()
{
    return socket->readAll();
}

qint64 QLocalSocketAdapter::write(const QString &str)
{
    return socket->write(str.toUtf8());
}

QString QLocalSocketAdapter::errorString() const
{
    return socket->errorString();
}

bool QLocalSocketAdapter::flush()
{
    return socket->flush();
}

void QLocalSocketAdapter::emitReadyRead()
{
    emit readyRead();
}

