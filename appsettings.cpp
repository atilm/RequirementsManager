#include "appsettings.h"

AppSettings::AppSettings()
{
    settings = new QSettings(QSettings::IniFormat,
                             QSettings::UserScope,
                             "TilmSoft",
                             "RequirementsManager");
    settings->setUserIniPath("./RequirementsManager.ini");
    defaultDirectory = ".";

    clear();
    load();
}

AppSettings::~AppSettings()
{
    delete settings;
}

void AppSettings::clear()
{
    startDirectory = defaultDirectory;
}

void AppSettings::load()
{
    startDirectory = settings->value("File/startDir").toString();
}

void AppSettings::save()
{
    settings->setValue("File/startDir", startDirectory);

    settings->sync();
}

QString AppSettings::directory() const
{
    return startDirectory;
}

void AppSettings::setDirectory(const QString &dir)
{
    startDirectory = dir;
}
