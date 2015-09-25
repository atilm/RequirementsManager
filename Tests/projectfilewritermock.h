#ifndef PROJECTFILEWRITERMOCK_H
#define PROJECTFILEWRITERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "projectfilewriter.h"

class ProjectFileWriterMock : public ProjectFileWriter {
 public:

    MOCK_METHOD2(save, void (RequirementsModel *model, const QString &filePath));
};

#endif // PROJECTFILEWRITERMOCK_H
