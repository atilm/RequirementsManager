#include "qtimeradapter.h"

QTimerAdapter::QTimerAdapter()
{
    timer = new QTimer();

    connect(timer, SIGNAL(timeout()), this, SIGNAL(timeout()));
}

QTimerAdapter::~QTimerAdapter()
{
    delete timer;
}

int QTimerAdapter::interval() const
{
    return timer->interval();
}

bool QTimerAdapter::isActive() const
{
    return timer->isActive();
}

bool QTimerAdapter::isSingleShot() const
{
    return timer->isSingleShot();
}

void QTimerAdapter::setInterval(int msec)
{
    timer->setInterval(msec);
}

void QTimerAdapter::setSingleShot(bool singleShot)
{
    timer->setSingleShot(singleShot);
}

int QTimerAdapter::timerId() const
{
    return timer->timerId();
}

void QTimerAdapter::emitTimeout()
{
    emit timeout();
}

void QTimerAdapter::start(int msec)
{
    timer->start(msec);
}

void QTimerAdapter::start()
{
    timer->start();
}

void QTimerAdapter::stop()
{
    timer->stop();
}
