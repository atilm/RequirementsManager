#ifndef QDIRADAPTER_H
#define QDIRADAPTER_H

#include <QDir>
#include <QString>
#include <QStringList>

class QDirAdapter
{
public:
    QDirAdapter();
    virtual ~QDirAdapter();
    virtual void setPath(const QString & path);
    virtual void setNameFilters(const QStringList & nameFilters) ;
    virtual QStringList entryList() const;

private:
    QDir d;
};

#endif // QDIRADAPTER_H
