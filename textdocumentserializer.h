#ifndef TEXTDOCUMENTSERIALIZER_H
#define TEXTDOCUMENTSERIALIZER_H

#include <QTextDocument>
#include <QTextCursor>
#include <QTextBlock>
#include <QTextFrame>
#include <QTextFragment>
#include "richtextresourcemanager.h"

class TextDocumentSerializer
{
public:
    TextDocumentSerializer(RichTextResourceManager *resources);
    virtual ~TextDocumentSerializer();

    virtual QString toSimpleHtml(QTextDocument *document);

private:
    RichTextResourceManager *resources;
    QTextDocument *document;

    QString processFrame(QTextFrame *frame);
    QString processBlock(QTextBlock block,
                         QTextFrame::iterator &it);
    QString processList(QTextList *list,
                        QTextFrame::iterator &it);
    QString processBlockContent(QTextBlock block);
    QString processFragment(QTextFragment fragment);
    QString getImageTag(QTextImageFormat format);
    QString removeTrailingLineBreaks(QString s);
};

#endif // TEXTDOCUMENTSERIALIZER_H
