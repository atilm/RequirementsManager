#ifndef QTEXTSTREAMADAPTERMOCK_H
#define QTEXTSTREAMADAPTERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "qtextstreamadapter.h"

class QTextStreamAdapterMock : public QTextStreamAdapter {
 public:

    MOCK_CONST_METHOD0(atEnd, bool ());
    MOCK_METHOD0(readLine, QString ());
    MOCK_METHOD0(readAll, QString ());
    MOCK_METHOD1(setDevice, void (QFileAdapter *device));
    MOCK_METHOD1(write, void (const QString &string));

};

#endif // QTEXTSTREAMADAPTERMOCK_H
