#include "filestatetracker.h"

FileStateTracker::FileStateTracker() : QObject()
{
    _filePath = "";
    _changed = false;
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

bool FileStateTracker::unsavedChanges() const
{
    return _changed;
}

void FileStateTracker::setChanged(bool state)
{
    if(state != _changed)
        emit changedStateChanged(state);

    _changed = state;
}
