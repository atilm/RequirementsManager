#include "version.h"

QString Version::versionNumberString()
{
    return QString("%1.%2.%3")
            .arg(VERSION_MAJOR)
            .arg(VERSION_MINOR, 2, 10, QLatin1Char('0'))
            .arg(VERSION_BUILD, 3, 10, QLatin1Char('0'));
}
