#ifndef PROJECTFILEREADERMOCK_H
#define PROJECTFILEREADERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "projectfilereader.h"

class ProjectFileReaderMock : public ProjectFileReader {
 public:
    MOCK_METHOD2(load, void (RequirementsModel *model, const QString &filePath));
};

#endif // PROJECTFILEREADERMOCK_H
