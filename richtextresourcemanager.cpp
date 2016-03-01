#include "richtextresourcemanager.h"
#include <QCryptographicHash>
#include <QFile>
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

QTextImageFormat RichTextResourceManager::insertImage(const QString &originalFilePath)
{
    QFileInfo originalInfo(originalFilePath);
    QFile file(originalFilePath);

    if(!file.open(QFile::ReadOnly))
        throw runtime_error("Could not open file.");

    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(&file);
    QString uniqueName = QString(hash.result().toHex());

    QDir imgDir = QDir(fileState->dir().absolutePath() + "/ReqManImages");

    if(!imgDir.exists())
        QDir().mkdir(imgDir.absolutePath());

    QFile::copy(originalFilePath, imgDir.absolutePath() + "/" + uniqueName + "." + originalInfo.suffix());

    QTextImageFormat format;

    return format;
}


