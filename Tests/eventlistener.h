#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <QObject>

//! Used in tests for file state tracker
class EventListener : public QObject
{
    Q_OBJECT
public:
    explicit EventListener(QObject *parent = 0);
    bool filePathChanged_called;
    bool changeStateChanged_called;

signals:

public slots:
    void setFilePathChanged(const QString &);
    void setChangedStateChanged(bool);

};

#endif // EVENTLISTENER_H
