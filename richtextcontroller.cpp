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
    QTextCursor cursor = edit->textCursor();

    if(on){
        QTextListFormat::Style style = QTextListFormat::ListDisc;

        cursor.beginEditBlock();
        QTextBlockFormat blockFormat = cursor.blockFormat();
        QTextListFormat listFormat;

        if(cursor.currentList()){
            listFormat = cursor.currentList()->format();
        }
        else{
            listFormat.setIndent(blockFormat.indent() + 1);
            blockFormat.setIndent(0);
            cursor.setBlockFormat(blockFormat);
        }

        listFormat.setStyle(style);
        cursor.createList(listFormat);
        cursor.endEditBlock();
    }
    else{
        QTextBlockFormat blockFormat;
        blockFormat.setObjectIndex(0);
        cursor.mergeBlockFormat(blockFormat);
        edit->setTextCursor(cursor);
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

    if(cursor.currentList())
        bulletAction->setChecked(true);
    else
        bulletAction->setChecked(false);
}

void RichTextController::handleInsertImage()
{
    edit->insertImage();
}

void RichTextController::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = edit->textCursor();
    cursor.mergeCharFormat(format);
    edit->mergeCurrentCharFormat(format);
}

