#ifndef APPSETTINGSMOCK_H
#define APPSETTINGSMOCK_H

#include "gmock/gmock.h"
#include "appsettings.h"

class AppSettingsMock : public AppSettings{
public:
    MOCK_CONST_METHOD0(directory, QString ());
    MOCK_METHOD1(setDirectory, void (const QString &dir));
};

#endif // APPSETTINGSMOCK_H
