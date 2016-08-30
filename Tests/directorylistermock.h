#ifndef DIRECTORYLISTERMOCK
#define DIRECTORYLISTERMOCK

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "directorylister.h"

class DirectoryListerMock : public DirectoryLister {
 public:

    DirectoryListerMock() : DirectoryLister(nullptr) {}

    MOCK_METHOD2(listFiles, QStringList (const QString &dirPath, const QString &regExp));
};

#endif // DIRECTORYLISTERMOCK

