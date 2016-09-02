#ifndef QTEXTSTREAMFAKE_H
#define QTEXTSTREAMFAKE_H

#include "qtextstreamadapter.h"

#include <QStringList>

class QTextStreamFake : public QTextStreamAdapter
{
public:
    QTextStreamFake();
    virtual ~QTextStreamFake();

    void setLines(const QStringList &list);

    virtual bool atEnd() const;
    virtual QString readLine();
    virtual QString readAll();
    virtual void setDevice(QFileAdapter *);
    virtual void write(const QString &);

private:
    QStringList lines;
};

#endif // QTEXTSTREAMFAKE_H
