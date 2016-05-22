#ifndef QTIMERADAPTER_H
#define QTIMERADAPTER_H

#include <QTimer>

class QTimerAdapter : public QObject
{
    Q_OBJECT
public:
    QTimerAdapter();
    virtual ~QTimerAdapter();

    virtual int  interval() const;
    virtual bool isActive() const;
    virtual bool isSingleShot() const;
    virtual void setInterval(int msec);
    virtual void setSingleShot(bool singleShot);
    virtual int  timerId() const;

    void emitTimeout();

signals:
    void timeout();

public slots:

    virtual void  start(int msec) ;
    virtual void  start();
    virtual void  stop();

private:
    QTimer *timer;
};

#endif // QTIMERADAPTER_H
