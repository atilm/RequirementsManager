#ifndef QSETTINGSADAPTER_H
#define QSETTINGSADAPTER_H

#include <QSettings>

class QSettingsAdapter
{
public:
    QSettingsAdapter(const QString &organization, const QString &application);
    virtual ~QSettingsAdapter();

    virtual void openIniFile(const QString &filePath);
    virtual void setValue(const QString &key, const QVariant &value);
    virtual QVariant value(const QString &key) const;
    virtual void sync();

private:
    QSettings *settings;
};

#endif // QSETTINGSADAPTER_H
