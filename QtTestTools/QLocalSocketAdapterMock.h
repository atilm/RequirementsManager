#ifndef QLOCALSOCKETADAPTERMOCK_H
#define QLOCALSOCKETADAPTERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "qlocalsocketadapter.h"

class QLocalSocketAdapterMock : public QLocalSocketAdapter
{
public:

    MOCK_METHOD2(connectToServer, void (const QString &name, QIODevice::OpenMode openMode));
    MOCK_METHOD0(disconnectFromServer, void ());
    MOCK_METHOD0(close, void ());
    MOCK_METHOD1(waitForConnected, bool (int msecs));
    MOCK_METHOD1(waitForBytesWritten, bool (int msecs));
    MOCK_METHOD0(readAll, QByteArray ());
    MOCK_METHOD1(write, qint64 (const QString &byteArray));
    MOCK_CONST_METHOD0(errorString, QString ());
    MOCK_METHOD0(flush, bool ());
    MOCK_CONST_METHOD0(isOpen, bool ());
};



#endif // QLOCALSOCKETADAPTERMOCK_H
