#ifndef DIRECTORYLISTER_H
#define DIRECTORYLISTER_H

#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QStringList>

#include <memory>
using namespace std;

class DirectoryLister
{
public:
    DirectoryLister(shared_ptr<QDir> dir);

    /*! List all file names in a directory which match a given pattern
     \param dirPath The directory in which to look for files
     \param regExp The pattern the file must match

     \return Absolute paths of files with matching names
     */
    virtual QStringList listFiles(const QString &dirPath, const QString &regExp);

private:
    shared_ptr<QDir> dir;
};

#endif // DIRECTORYLISTER_H
