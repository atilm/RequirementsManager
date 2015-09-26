#include "filestatetracker.h"

FileStateTracker::FileStateTracker() : QObject()
{
}

FileStateTracker::~FileStateTracker()
{

}

QString FileStateTracker::filePath() const
{
    return QString();
}

void FileStateTracker::setFilePath(const QString &path)
{

}

void FileStateTracker::setChanged(bool state)
{

}
