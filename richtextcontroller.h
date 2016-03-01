#ifndef RICHTEXTCONTROLLER_H
#define RICHTEXTCONTROLLER_H

#include "descriptionview.h"
#include <QTextEdit>
#include <QAction>

class RichTextController : QObject
{
    Q_OBJECT
public:
    RichTextController();

    virtual void setTextEdit(DescriptionView *edit);
    virtual void setBoldAction(QAction *boldAction);
    virtual void setItalicAction(QAction *italicAction);
    virtual void setBulletAction(QAction *bulletAction);
    virtual void setInsertImageAction(QAction *imageAction);

private:
    DescriptionView *edit;
    QAction *boldAction;
    QAction *italicAction;
    QAction *bulletAction;
    QAction *imageAction;

private slots:
    void handleBoldToggled(bool on);
    void handleBulletToggled(bool on);
    void handleFormatChanged(QTextCharFormat format); 
    void handleInsertImage();
};

#endif // RICHTEXTCONTROLLER_H
