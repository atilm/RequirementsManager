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

    void processFrame(QTextFrame *frame);
    void processBlock(QTextBlock block);
    void processFragment(QTextFragment fragment);
};

#endif // TEXTDOCUMENTSERIALIZER_H
