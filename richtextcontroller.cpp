#include "richtextcontroller.h"
#include <QTextList>
#include <QTextCursor>

RichTextController::RichTextController()
{
    edit = NULL;
    italicAction = NULL;
    boldAction = NULL;
    bulletAction = NULL;
}

void RichTextController::setTextEdit(QTextEdit *edit)
{
    this->edit = edit;
    connect(edit, SIGNAL(currentCharFormatChanged(QTextCharFormat)), this, SLOT(handleFormatChanged(QTextCharFormat)));

    if(italicAction){
        connect(italicAction, SIGNAL(toggled(bool)), edit, SLOT(setFontItalic(bool)));
    }
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
}

void RichTextController::setBulletAction(QAction *bulletAction)
{
    this->bulletAction = bulletAction;
    bulletAction->setCheckable(true);
    connect(bulletAction, SIGNAL(toggled(bool)), this, SLOT(handleBulletToggled(bool)));
}

void RichTextController::handleBoldToggled(bool on)
{
    if(on)
        edit->setFontWeight(QFont::Bold);
    else
        edit->setFontWeight(QFont::Normal);
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
    if(format.fontWeight() == QFont::Normal)
        boldAction->setChecked(false);
    else
        boldAction->setChecked(true);

    italicAction->setChecked(format.fontItalic());

    if(format.isListFormat()){
        if( edit->textCursor().currentList()->formatIndex() == QTextListFormat::ListDisc )
            bulletAction->setChecked(true);
        else
            bulletAction->setChecked(false);
    }
    else
        bulletAction->setChecked(false);
}

