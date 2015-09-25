#ifndef FILESTATETRACKER_H
#define FILESTATETRACKER_H

#include <QObject>
#include <QString>

class FileStateTracker : public QObject
{
    Q_OBJECT
public:
    FileStateTracker();
    virtual ~FileStateTracker();

    virtual void setFilePath(const QString &path);
};

#endif // FILESTATETRACKER_H
