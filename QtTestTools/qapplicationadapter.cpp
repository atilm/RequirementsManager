#include "qapplicationadapter.h"

#include <QApplication>

QApplicationAdapter::QApplicationAdapter()
{
}

QApplicationAdapter::~QApplicationAdapter()
{
}

void QApplicationAdapter::quit()
{
    exit(0);
}
