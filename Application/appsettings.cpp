#include "appsettings.h"

AppSettings::AppSettings()
{
    settings = new QSettings(QSettings::IniFormat,
                             QSettings::UserScope,
                             "TilmSoft",
                             "RequirementsManager");
    settings->setUserIniPath("./RequirementsManager.ini");
    defaultDirectory = ".";
    showIDs = false;

    clear();
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
    showIDs = settings->value("Application/showIDs").toBool();
}

void AppSettings::save()
{
    settings->setValue("File/startDir", startDirectory);
    settings->setValue("Application/showIDs", showIDs);

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

bool AppSettings::idIsVisible() const
{
    return showIDs;
}

void AppSettings::setIDVisible(bool value)
{
    showIDs = value;
}
