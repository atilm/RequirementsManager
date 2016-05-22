#include "qsettingsadapter.h"

QSettingsAdapter::QSettingsAdapter(const QString &organization, const QString &application)
{
    settings = new QSettings(organization, application);
}

QSettingsAdapter::~QSettingsAdapter()
{
    delete settings;
}

void QSettingsAdapter::openIniFile(const QString &filePath)
{
    delete settings;

    settings = new QSettings(filePath, QSettings::IniFormat);
}

void QSettingsAdapter::setValue(const QString &key, const QVariant &value)
{
    settings->setValue(key, value);
}

QVariant QSettingsAdapter::value(const QString &key) const
{
    return settings->value(key);
}

void QSettingsAdapter::sync()
{
    settings->sync();
}
