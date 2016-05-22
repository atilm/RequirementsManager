#ifndef QDIRADAPTERMOCK_H
#define QDIRADAPTERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "qdiradapter.h"

class QDirAdapterMock : public QDirAdapter {
 public:

    MOCK_METHOD1(setPath, void (const QString & path));
    MOCK_METHOD1(setNameFilters, void (const QStringList & nameFilters));
    MOCK_CONST_METHOD0(entryList, QStringList ());

};

#endif // QDIRADAPTERMOCK_H
