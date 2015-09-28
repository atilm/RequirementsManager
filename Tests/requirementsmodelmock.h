#ifndef REQUIREMENTSMODELMOCK_H
#define REQUIREMENTSMODELMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "requirementsmodel.h"

class RequirementsModelMock : public RequirementsModel {
 public:

    RequirementsModelMock() : RequirementsModel(NULL, NULL) {}

    MOCK_METHOD2(save, void (RequirementsModel *model, const QString &filePath));
    MOCK_METHOD0(clearModel, void ());
};

#endif // REQUIREMENTSMODELMOCK_H
