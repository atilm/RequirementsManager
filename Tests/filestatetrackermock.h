#ifndef FILESTATETRACKERMOCK_H
#define FILESTATETRACKERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "filestatetracker.h"

class FileStateTrackerMock : public FileStateTracker {
 public:

    MOCK_METHOD1(setFilePath, void (const QString &path));
};

#endif // FILESTATETRACKERMOCK_H
