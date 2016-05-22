#ifndef QLOCALSOCKETADAPTER_H
#define QLOCALSOCKETADAPTER_H

#include <QLocalSocket>
#include <QObject>
#include <QIODevice>

class QLocalSocketAdapter : public QObject
{
    Q_OBJECT
public:
    explicit QLocalSocketAdapter(QObject *parent = 0);
    virtual ~QLocalSocketAdapter();

    virtual void connectToServer(const QString &name, QIODevice::OpenMode openMode = QIODevice::ReadWrite);
    virtual void disconnectFromServer();
    virtual void close();
    virtual bool isOpen() const;

    virtual bool waitForConnected(int msecs);
    virtual bool waitForBytesWritten(int msecs);

    virtual QByteArray readAll();
    virtual qint64 write(const QString &str);

    virtual QString errorString() const;
    virtual bool flush();

    void emitReadyRead();

signals:
    void readyRead();
    
private:
    QLocalSocket *socket;
};

#endif // QLOCALSOCKETADAPTER_H
