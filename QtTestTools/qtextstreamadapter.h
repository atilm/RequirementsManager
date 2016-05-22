#ifndef QTEXTSTREAMADAPTER_H
#define QTEXTSTREAMADAPTER_H

#include "qfileadapter.h"
#include <QTextStream>

class QTextStreamAdapter
{
public:
    QTextStreamAdapter();
    virtual ~QTextStreamAdapter();
    virtual bool atEnd() const;
    virtual QString readLine();
    virtual QString readAll();
    virtual void setDevice(QFileAdapter *device);
    virtual void write(const QString &string);

private:
    QTextStream *stream;
};

#endif // QTEXTSTREAMADAPTER_H
