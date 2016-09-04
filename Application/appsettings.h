#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QMainWindow>
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

    virtual void saveGeometry(QMainWindow *window);
    virtual void restoreGeometry(QMainWindow *window);

    virtual QString directory() const;
    virtual void setDirectory(const QString &dir);

    bool idIsVisible() const;
    void setIDVisible(bool value);

private:
    QSettings *settings;
    QString defaultDirectory;
    QString startDirectory;
    bool showIDs;
};

#endif // APPSETTINGS_H
