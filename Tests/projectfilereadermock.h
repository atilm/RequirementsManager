#ifndef PROJECTFILEREADERMOCK_H
#define PROJECTFILEREADERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "projectfilereader.h"

class ProjectFileReaderMock : public ProjectFileReader {
 public:
    ProjectFileReaderMock() : ProjectFileReader(NULL, NULL) {}

    MOCK_METHOD2(load, void (ProjectFileController *fileController, QFileAdapter *file));
};

#endif // PROJECTFILEREADERMOCK_H
