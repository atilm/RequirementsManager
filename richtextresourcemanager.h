#ifndef RICHTEXTRESOURCEMANAGER_H
#define RICHTEXTRESOURCEMANAGER_H

#include "filestatetracker.h"
#include <QTextDocument>
#include <QTextImageFormat>

class RichTextResourceManager
{
public:
    RichTextResourceManager(FileStateTracker *fileState);
    virtual ~RichTextResourceManager();

    virtual void setDocument(QTextDocument *document);
    virtual QUrl insertImage(const QString &originalFilePath);
    virtual QUrl insertImage(QImage image);
    virtual void loadResources(const QString &html);
    virtual void saveImage(QString uri);

    virtual QString imageFolderName() const;

private:
    FileStateTracker *fileState;
    QTextDocument *document;

    QString getUniqueName(const QString &path);
    QString getUniqueFileName(const QImage &image);
    QStringList extractFileNames(const QString &html);
    void loadResource(const QString &archiveFileName);
    QUrl loadResource(const QString &sourceFileName,
                      const QString &archiveFileName);
};

#endif // RICHTEXTRESOURCEMANAGER_H
