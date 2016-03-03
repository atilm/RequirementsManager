#ifndef TEXTDOCUMENTSERIALIZER_H
#define TEXTDOCUMENTSERIALIZER_H

#include <QTextDocument>
#include <QTextCursor>
#include <QTextBlock>
#include <QTextFrame>
#include <QTextFragment>

class TextDocumentSerializer
{
public:
    TextDocumentSerializer();
    virtual ~TextDocumentSerializer();

    virtual QString toSimpleHtml(QTextDocument *document);

private:

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
