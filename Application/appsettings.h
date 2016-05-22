#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QSettings>

class AppSettings
{
public:
    AppSettings();
    virtual ~AppSettings();

    virtual void clear();
    virtual void load();
    virtual void save();

    virtual QString directory() const;
    virtual void setDirectory(const QString &dir);

private:
    QSettings *settings;
    QString defaultDirectory;
    QString startDirectory;
};

#endif // APPSETTINGS_H
