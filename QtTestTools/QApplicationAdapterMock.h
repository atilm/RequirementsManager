#ifndef QAPPLICATIONADAPTERMOCK_H
#define QAPPLICATIONADAPTERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "qapplicationadapter.h"

class QApplicationAdapterMock : public QApplicationAdapter {
 public:

    MOCK_METHOD0(quit, void ());

};

#endif // QAPPLICATIONADAPTERMOCK_H
