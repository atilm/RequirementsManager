#ifndef PROJECTFILEWRITERMOCK_H
#define PROJECTFILEWRITERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "projectfilewriter.h"

class ProjectFileWriterMock : public ProjectFileWriter {
 public:
    ProjectFileWriterMock() : ProjectFileWriter(NULL, NULL, NULL) {}

    MOCK_METHOD2(save, void (ProjectFileController *fileController, QFileAdapter *file));
};

#endif // PROJECTFILEWRITERMOCK_H
