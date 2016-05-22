#ifndef QCOREAPPLICATIONADAPTER_H
#define QCOREAPPLICATIONADAPTER_H

#include <QCoreApplication>

class QCoreApplicationAdapter
{
public:
    QCoreApplicationAdapter();
    virtual ~QCoreApplicationAdapter();

    virtual QString applicationDirPath();
};

#endif // QCOREAPPLICATIONADAPTER_H
