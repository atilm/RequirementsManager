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
    virtual QTextImageFormat insertImage(const QString &originalFilePath);

private:
    FileStateTracker *fileState;
    QTextDocument *document;
};

#endif // RICHTEXTRESOURCEMANAGER_H
