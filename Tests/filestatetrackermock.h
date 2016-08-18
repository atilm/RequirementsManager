#ifndef FILESTATETRACKERMOCK_H
#define FILESTATETRACKERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "filestatetracker.h"

class FileStateTrackerMock : public FileStateTracker {
 public:

    MOCK_METHOD1(setFilePath, void (const QString &path));
    MOCK_CONST_METHOD0(filePath, QString ());
    MOCK_METHOD1(setChanged, void (bool state));
    MOCK_CONST_METHOD0(unsavedChanges, bool ());
};

#endif // FILESTATETRACKERMOCK_H
