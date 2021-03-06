#ifndef RICHTEXTRESOURCEMANAGER_H
#define RICHTEXTRESOURCEMANAGER_H

#include "filestatetracker.h"
#include <QTextDocument>
#include <QTextImageFormat>

class RichTextResourceManager
{
public:
    RichTextResourceManager(shared_ptr<FileStateTracker> fileState);
    virtual ~RichTextResourceManager();

    virtual void setDocument(QTextDocument *document);
    virtual QUrl insertImage(const QString &originalFilePath);
    virtual QUrl insertImage(QImage image);
    virtual void loadResources(const QString &html);
    virtual void saveImage(QString uri);

    virtual QString imageFolderName() const;
    virtual void beginSavingResources();
    virtual void endSavingResources();

private:
    shared_ptr<FileStateTracker> fileState;
    QTextDocument *document;
    QStringList presentFiles;

    QDir getImageDirectory() const;
    QString getUniqueName(const QString &path);
    QString getUniqueFileName(const QImage &image);
    QStringList extractFileNames(const QString &html);
    void loadResource(const QString &archiveFileName);
    QUrl loadResource(const QString &sourceFileName,
                      const QString &archiveFileName);
};

#endif // RICHTEXTRESOURCEMANAGER_H
