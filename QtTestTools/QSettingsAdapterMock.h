#ifndef QSETTINGSADAPTERMOCK_H
#define QSETTINGSADAPTERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "qsettingsadapter.h"

class QSettingsAdapterMock : public QSettingsAdapter
{
public:
    QSettingsAdapterMock(const QString &organization, const QString &application) :
        QSettingsAdapter(organization, application) {}

    MOCK_METHOD1(openIniFile, void (const QString &filePath));
    MOCK_METHOD2(setValue, void (const QString &key, const QVariant &value));
    MOCK_CONST_METHOD1(value, QVariant (const QString &key));
    MOCK_METHOD0(sync, void ());
};

#endif // QSETTINGSADAPTERMOCK_H
