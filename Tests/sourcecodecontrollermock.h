#ifndef SOURCECODECONTROLLERMOCK_H
#define SOURCECODECONTROLLERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "sourcecodecontroller.h"

class SourceCodeControllerMock : public SourceCodeController {
 public:
    SourceCodeControllerMock() : SourceCodeController(nullptr, nullptr,
                                                      nullptr, nullptr,
                                                      nullptr, nullptr) {}

};

#endif // SOURCECODECONTROLLERMOCK_H
