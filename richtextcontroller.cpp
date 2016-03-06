#include "richtextcontroller.h"
#include <QDebug>
#include <QTextList>
#include <QTextCursor>

RichTextController::RichTextController()
{
    edit = NULL;
    italicAction = NULL;
    boldAction = NULL;
    bulletAction = NULL;
}

void RichTextController::setTextEdit(DescriptionView *edit)
{
    this->edit = edit;
    connect(edit, SIGNAL(currentCharFormatChanged(QTextCharFormat)), this, SLOT(handleFormatChanged(QTextCharFormat)));
    connect(edit, SIGNAL(cursorPositionChanged()), this, SLOT(handleCursorPositionChanged()));
}

void RichTextController::setBoldAction(QAction *boldAction)
{
    this->boldAction = boldAction;
    boldAction->setCheckable(true);
    connect(boldAction, SIGNAL(toggled(bool)), this, SLOT(handleBoldToggled(bool)));
}

void RichTextController::setItalicAction(QAction *italicAction)
{
    this->italicAction = italicAction;
    italicAction->setCheckable(true);
    connect(italicAction, SIGNAL(toggled(bool)), this, SLOT(handleItalicToggled(bool)));
}

void RichTextController::setBulletAction(QAction *bulletAction)
{
    this->bulletAction = bulletAction;
    bulletAction->setCheckable(true);
    connect(bulletAction, SIGNAL(toggled(bool)), this, SLOT(handleBulletToggled(bool)));
}

void RichTextController::setInsertImageAction(QAction *imageAction)
{
    this->imageAction = imageAction;
    connect(imageAction, SIGNAL(triggered(bool)), this, SLOT(handleInsertImage()));
}

void RichTextController::handleBoldToggled(bool on)
{
    QTextCharFormat fmt;
    fmt.setFontWeight(on ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}

void RichTextController::handleItalicToggled(bool on)
{
    QTextCharFormat fmt;
    fmt.setFontItalic(on);
    mergeFormatOnWordOrSelection(fmt);
}

void RichTextController::handleBulletToggled(bool on)
{
    if(on){
        QTextCursor cursor = edit->textCursor();
        QTextListFormat listFormat;
        listFormat.setStyle(QTextListFormat::ListDisc);
        cursor.createList(listFormat);
    }
    else{
        QTextCursor cursor = edit->textCursor();
        QTextList *list = cursor.currentList();
        if( list ) {
            QTextListFormat listFormat;
            listFormat.setIndent(0);
            list->setFormat(listFormat);

            for(int i = list->count() - 1; i >= 0; --i)
                list->removeItem( i );
        }
    }
}

void RichTextController::handleFormatChanged(QTextCharFormat format)
{
    boldAction->setChecked(format.fontWeight() > QFont::Normal);
    italicAction->setChecked(format.fontItalic());
}

void RichTextController::handleCursorPositionChanged()
{
    QTextCursor cursor = edit->textCursor();
    QTextBlockFormat blockFormat = cursor.blockFormat();

    bulletAction->setChecked(blockFormat.isListFormat());
}

void RichTextController::handleInsertImage()
{
    edit->insertImage();
}

void RichTextController::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = edit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    edit->mergeCurrentCharFormat(format);
}

