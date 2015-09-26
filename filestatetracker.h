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

    virtual QString filePath() const;
    virtual void setFilePath(const QString &path);
    virtual void setChanged(bool state);
};

#endif // FILESTATETRACKER_H
