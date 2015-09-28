#include "filestatetracker.h"

FileStateTracker::FileStateTracker() : QObject()
{
    _filePath = "";
    changed = false;
}

FileStateTracker::~FileStateTracker()
{

}

QString FileStateTracker::filePath() const
{
    return _filePath;
}

void FileStateTracker::setFilePath(const QString &path)
{
    if(path != _filePath)
        emit filePathChanged(path);

    _filePath = path;
}

void FileStateTracker::setChanged(bool state)
{
    if(state != changed)
        emit changedStateChanged(state);

    changed = state;
}
