#ifndef QFILEADAPTERMOCK_H
#define QFILEADAPTERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "qfileadapter.h"

class QFileAdapterMock : public QFileAdapter {
 public:

    MOCK_METHOD1(open, bool (QFile::OpenMode mode));
    MOCK_METHOD0(close, void ());
    MOCK_METHOD1(setFileName, void (const QString & name));

};

#endif // QFILEADAPTERMOCK_H
