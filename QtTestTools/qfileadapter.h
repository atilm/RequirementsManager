#ifndef QFILEADAPTER_H
#define QFILEADAPTER_H

#include <QString>
#include <QFile>

class QFileAdapter : public QFile
{
public:
    QFileAdapter();
    virtual ~QFileAdapter();
    virtual bool open(QFile::OpenMode mode);
    virtual void close();
    virtual void setFileName(const QString & name);
};

#endif // QFILEADAPTER_H
