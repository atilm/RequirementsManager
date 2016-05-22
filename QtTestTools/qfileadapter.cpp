#include "qfileadapter.h"

QFileAdapter::QFileAdapter() : QFile()
{
}

QFileAdapter::~QFileAdapter()
{
}

bool QFileAdapter::open(QIODevice::OpenMode mode)
{
    return QFile::open(mode);
}

void QFileAdapter::close()
{
    QFile::close();
}


void QFileAdapter::setFileName(const QString &name)
{
    QFile::setFileName(name);
}
