#include "textdocumentserializer.h"
#include <QDebug>
#include <QTextFragment>

TextDocumentSerializer::TextDocumentSerializer()
{

}

TextDocumentSerializer::~TextDocumentSerializer()
{

}

QString TextDocumentSerializer::toSimpleHtml(QTextDocument *document)
{
    QTextFrame *root = document->rootFrame();
    processFrame(root);

    return QString();
}

void TextDocumentSerializer::processFrame(QTextFrame *frame)
{
    QTextFrame::iterator it = frame->begin();
    while(!it.atEnd()){
        QTextFrame *childFrame = it.currentFrame();
        QTextBlock childBlock = it.currentBlock();

        if(childFrame)
            processFrame(childFrame);
        else if(childBlock.isValid())
            processBlock(childBlock);

        ++it;
    }
}

void TextDocumentSerializer::processBlock(QTextBlock block)
{
    QTextBlock::iterator it = block.begin();

    while(!it.atEnd()){
        QTextFragment currentFragment = it.fragment();

        if (currentFragment.isValid())
            processFragment(currentFragment);

        ++it;
    }
}

void TextDocumentSerializer::processFragment(QTextFragment fragment)
{
    qDebug() << QString("frag: %1").arg(fragment.text());
}

