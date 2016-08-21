#include "eventlistener.h"

EventListener::EventListener(QObject *parent) :
    QObject(parent)
{
    filePathChanged_called = false;
    changeStateChanged_called = false;
}

void EventListener::setFilePathChanged(const QString &) {
    filePathChanged_called = true;
}

void EventListener::setChangedStateChanged(bool) {
    changeStateChanged_called = true;
}
