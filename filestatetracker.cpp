#include "filestatetracker.h"
#include <QFileInfo>
#include <QDir>

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

QDir FileStateTracker::dir() const
{
    QFileInfo fInfo(_filePath);
    QDir directory(fInfo.absoluteDir());
    return directory;
}

void FileStateTracker::setFilePath(const QString &path)
{
    if(path != _filePath)
        emit filePathChanged(path);

    _filePath = path;
}

QString FileStateTracker::toAbsoluteFilePath(const QString relativePath)
{
    QFileInfo fInfo(_filePath);
    QDir dir(fInfo.absoluteDir());
    return dir.absoluteFilePath(relativePath);
}

QString FileStateTracker::toRelativeFilePath(const QString absolutePath)
{
    QFileInfo fInfo(_filePath);
    QDir dir(fInfo.absoluteDir());
    return dir.relativeFilePath(absolutePath);
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
