#ifndef RISKASSESSMENTMODELMOCK
#define RISKASSESSMENTMODELMOCK


#include "gmock/gmock.h"  // Brings in Google Mock.
#include "riskassessmentmodel.h"

class RiskAssessmentModelMock : public RiskAssessmentModel {
 public:
    RiskAssessmentModelMock() : RiskAssessmentModel(nullptr, nullptr) {}

};


#endif // RISKASSESSMENTMODELMOCK

