#include "richtextresourcemanager.h"
#include <QBuffer>
#include <QCryptographicHash>
#include <QDebug>
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

    return loadResource(originalFilePath, uniqueFileName);
}

QUrl RichTextResourceManager::insertImage(QImage image)
{
    QString uniqueFileName = getUniqueFileName(image);

    QUrl uri(QString("file://%1").arg(uniqueFileName));
    document->addResource(QTextDocument::ImageResource, uri, QVariant(image));
    return uri;
}

void RichTextResourceManager::loadResources(const QString &html)
{
    QStringList fileList = extractFileNames(html);

    foreach(QString name, fileList)
        loadResource(name);
}

void RichTextResourceManager::saveImage(QString uri)
{
    QDir imgDir = getImageDirectory();

    if(!imgDir.exists())
        QDir().mkdir(imgDir.absolutePath());

    QString uniqueFileName = uri;
    uniqueFileName.replace("file://", "");

    QString archivePath = imgDir.absolutePath() + "/" + uniqueFileName;

    QFileInfo fInfo(archivePath);

    if(!fInfo.exists()){
        QImage image = document->resource(QTextDocument::ImageResource, uri).value<QImage>();
        image.save(archivePath);
    }

    presentFiles.removeOne(uniqueFileName);
}

QString RichTextResourceManager::imageFolderName() const
{
    return fileState->fileBaseName() + "Images";
}

void RichTextResourceManager::beginSavingResources()
{
    QDir imgDir = getImageDirectory();
    imgDir.setFilter(QDir::Files);
    presentFiles = imgDir.entryList();
}

void RichTextResourceManager::endSavingResources()
{
    QDir imgDir = getImageDirectory();
    foreach(QString file, presentFiles)
        imgDir.remove(file);

    presentFiles.clear();
}

QDir RichTextResourceManager::getImageDirectory() const
{
    return QDir(fileState->dir().absolutePath() + "/" + imageFolderName());
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

QString RichTextResourceManager::getUniqueFileName(const QImage &image)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(byteArray);
    return QString("%1.png").arg(QString(hash.result().toHex()));
}

QStringList RichTextResourceManager::extractFileNames(const QString &html)
{
    int start = 0;
    int stop = 0;

    QString marker = QString("./%1/").arg(imageFolderName());

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
    QString archivePath = QString("%1/%2/%3").arg(fileState->dir().absolutePath())
                                             .arg(imageFolderName())
                                             .arg(archiveFileName);
    QUrl uri(QString("file://%1").arg(archiveFileName));
    QImage image = QImageReader(archivePath).read();
    document->addResource(QTextDocument::ImageResource, uri, QVariant(image));
}

QUrl RichTextResourceManager::loadResource(const QString &sourceFileName, const QString &archiveFileName)
{
    QUrl uri(QString("file://%1").arg(archiveFileName));
    QImage image = QImageReader(sourceFileName).read();
    document->addResource(QTextDocument::ImageResource, uri, QVariant(image));
    return uri;
}


