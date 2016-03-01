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
    virtual void loadResources(const QString &html);

private:
    FileStateTracker *fileState;
    QTextDocument *document;

    QString getUniqueName(const QString &path);
    QStringList extractFileNames(const QString &html);
    void loadResource(const QString &archiveFileName);
};

#endif // RICHTEXTRESOURCEMANAGER_H
