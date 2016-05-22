#ifndef QCOREAPPLICATIONADAPTERMOCK_H
#define QCOREAPPLICATIONADAPTERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "qcoreapplicationadapter.h"

class QCoreApplicationAdapterMock : public QCoreApplicationAdapter {
 public:

    MOCK_METHOD0(applicationDirPath, QString ());

};

#endif // QCOREAPPLICATIONADAPTERMOCK_H
