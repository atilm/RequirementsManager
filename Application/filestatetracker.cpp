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

QString FileStateTracker::fileBaseName() const
{
    QFileInfo fInfo(_filePath);
    return fInfo.baseName();
}

QDir FileStateTracker::dir() const
{
    QFileInfo fInfo(_filePath);
    QDir directory(fInfo.absoluteDir());
    return directory;
}

void FileStateTracker::setFilePath(const QString &path)
{
    QString previousPath = _filePath;

    _filePath = path;

    if(_filePath != previousPath)
        emit filePathChanged(path);
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
    bool previousState = _changed;

    _changed = state;

    if(_changed != previousState)
        emit changedStateChanged(_changed);
}
