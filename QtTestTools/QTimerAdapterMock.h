#ifndef QTIMERADAPTERMOCK_H
#define QTIMERADAPTERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "qtimeradapter.h"

class QTimerAdapterMock : public QTimerAdapter {
 public:

    MOCK_CONST_METHOD0(interval, int ());
    MOCK_CONST_METHOD0(isActive, bool ());
    MOCK_CONST_METHOD0(isSingleShot, bool ());
    MOCK_METHOD1(setInterval, void (int msec));
    MOCK_METHOD1(setSingleShot, void (bool singleShot));
    MOCK_CONST_METHOD0(timerId, int ());
    MOCK_METHOD1(start, void (int msec));
    MOCK_METHOD0(start, void ());
    MOCK_METHOD0(stop, void ());
};

#endif // QTIMERADAPTERMOCK_H
