#include "richtextresourcemanager.h"
#include <QCryptographicHash>
#include <QFile>
#include <QImageReader>
#include <QUrl>
#include <QString>
#include <stdexcept>
using namespace std;

RichTextResourceManager::RichTextResourceManager(FileStateTracker *fileState)
{
    this->fileState = fileState;
}

RichTextResourceManager::~RichTextResourceManager()
{

}

void RichTextResourceManager::setDocument(QTextDocument *document)
{
    this->document = document;
}

QUrl RichTextResourceManager::insertImage(const QString &originalFilePath)
{
    QFileInfo fInfo(originalFilePath);
    QString uniqueFileName = getUniqueName(originalFilePath) + "." + fInfo.suffix();

    QDir imgDir = QDir(fileState->dir().absolutePath() + "/ReqManImages");

    if(!imgDir.exists())
        QDir().mkdir(imgDir.absolutePath());

    QString archivePath = imgDir.absolutePath() + "/" + uniqueFileName;

    QFile::copy(originalFilePath, archivePath);

    loadResource(uniqueFileName);

    QUrl uri(QString("file://%1").arg(uniqueFileName));

    return uri;
}

void RichTextResourceManager::loadResources(const QString &html)
{
    QStringList fileList = extractFileNames(html);

    foreach(QString name, fileList)
        loadResource(name);
}

QString RichTextResourceManager::getUniqueName(const QString &path)
{
    QFile file(path);

    if(!file.open(QFile::ReadOnly))
        throw runtime_error("Could not open file.");

    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(&file);
    QString uniqueName = QString(hash.result().toHex());

    return uniqueName;
}

QStringList RichTextResourceManager::extractFileNames(const QString &html)
{
    int start = 0;
    int stop = 0;

    QString marker("file://");
    QStringList fileList;

    while(true){
        start = html.indexOf(marker, stop);

        if(start == -1)
            break;

        start += marker.length();
        stop = html.indexOf("\"", start);
        fileList.append(html.mid(start, stop - start));
    }

    return fileList;
}

void RichTextResourceManager::loadResource(const QString &archiveFileName)
{
    QString archivePath = fileState->dir().absolutePath() + "/ReqManImages/" + archiveFileName;
    QUrl uri(QString("file://%1").arg(archiveFileName));
    QImage image = QImageReader(archivePath).read();
    document->addResource(QTextDocument::ImageResource, uri, QVariant(image));
}


