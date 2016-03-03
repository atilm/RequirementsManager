#include "textdocumentserializer.h"
#include <QDebug>
#include <QTextFragment>
#include <QTextList>

TextDocumentSerializer::TextDocumentSerializer()
{

}

TextDocumentSerializer::~TextDocumentSerializer()
{

}

QString TextDocumentSerializer::toSimpleHtml(QTextDocument *document)
{
    QTextFrame *root = document->rootFrame();
    return processFrame(root);
}

QString TextDocumentSerializer::processFrame(QTextFrame *frame)
{
    QString text;

    QTextFrame::iterator it = frame->begin();
    while(!it.atEnd()){
        QTextFrame *childFrame = it.currentFrame();
        QTextBlock childBlock = it.currentBlock();

        if(childFrame)
            text += processFrame(childFrame);
        else if(childBlock.isValid()){
            text += processBlock(childBlock, it);
        }

        ++it;
    }

    text = removeTrailingLineBreaks(text);

    return text;
}

QString TextDocumentSerializer::processBlock(QTextBlock block,
                                             QTextFrame::iterator &it)
{
    QTextList *list = block.textList();

    if(list)
        return processList(list, it);
    else
        return processBlockContent(block);
}

QString TextDocumentSerializer::processList(QTextList *list,
                                            QTextFrame::iterator &it)
{
    QString text;

    for(int i=0; i < list->count(); i++){
        text += processBlockContent(list->item(i));
        ++it;
    }

    return QString("<ul>%1</ul>").arg(text);
}

QString TextDocumentSerializer::processBlockContent(QTextBlock block)
{
    QTextBlock::iterator it = block.begin();

    QString text;

    while(!it.atEnd()){
        QTextFragment currentFragment = it.fragment();

        if (currentFragment.isValid())
            text += processFragment(currentFragment);

        ++it;
    }

    if(block.textList())
        return QString("<li>%1</li>").arg(text);
    else
        return QString("%1<br>").arg(text);

}

QString TextDocumentSerializer::processFragment(QTextFragment fragment)
{
    QTextCharFormat format = fragment.charFormat();

    QString text = fragment.text();

    if(format.isImageFormat())
        text = getImageTag(format.toImageFormat());

    if(format.fontWeight() == QFont::Bold)
        text = QString("<b>%1</b>").arg(text);

    if(format.fontItalic())
        text = QString("<i>%1</i>").arg(text);

    text = text.replace(QChar(0x2028), "<br>");

    return text;
}

QString TextDocumentSerializer::getImageTag(QTextImageFormat format)
{
    int width = format.width();
    int height = format.height();

    QString text;

    if(width == 0 || height == 0)
        text = QString("<img src=\"%1\">").arg(format.name());
    else
        text = QString("<img src=\"%1\" width=\"%2\" height=\"%3\">")
                .arg(format.name())
                .arg(width)
                .arg(height);

    return text;
}

QString TextDocumentSerializer::removeTrailingLineBreaks(QString s)
{
    while(s.endsWith("<br>")){
        s.chop(4);
    }

    return s;
}

