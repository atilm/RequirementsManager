#include "qdiradapter.h"

QDirAdapter::QDirAdapter()
{
}

QDirAdapter::~QDirAdapter()
{
}

void QDirAdapter::setPath(const QString &path)
{
    d.setPath(path);
}

void QDirAdapter::setNameFilters(const QStringList &nameFilters)
{
    d.setNameFilters(nameFilters);
}

QStringList QDirAdapter::entryList() const
{
    return d.entryList();
}
