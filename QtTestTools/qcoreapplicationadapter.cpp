#include "qcoreapplicationadapter.h"

QCoreApplicationAdapter::QCoreApplicationAdapter()
{
}

QCoreApplicationAdapter::~QCoreApplicationAdapter()
{
}

QString QCoreApplicationAdapter::applicationDirPath()
{
    return QCoreApplication::applicationDirPath();
}
