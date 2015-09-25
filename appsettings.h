#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>

class AppSettings
{
public:
    AppSettings();
    virtual ~AppSettings();

    virtual QString directory() const;
    virtual void setDirectory(const QString &dir);
};

#endif // APPSETTINGS_H
