#include "directorylister.h"

DirectoryLister::DirectoryLister(shared_ptr<QDir> dir)
{
    this->dir = dir;
}

QStringList DirectoryLister::listFiles(const QString &dirPath,
                                           const QString &regExp)
{
    QStringList files;

    dir->setPath(dirPath);
    QFileInfoList entries = dir->entryInfoList(QDir::Files);

    QRegExp rx(regExp);

    for(int f=0;f<entries.count();f++){
        QFileInfo entry = entries[f];
        if(rx.exactMatch(entry.fileName()))
            files << entry.absoluteFilePath();
    }

    return files;
}

