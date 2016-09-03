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
    virtual void setCodeAction(QAction *codeAction);
    virtual void setBulletAction(QAction *bulletAction);
    virtual void setInsertImageAction(QAction *imageAction);

private slots:
    void handleBoldToggled(bool on);
    void handleItalicToggled(bool on);
    void handleCodeToggled(bool on);
    void handleBulletToggled(bool on);
    void handleFormatChanged(QTextCharFormat format); 
    void handleCursorPositionChanged();
    void handleInsertImage();

private:
    DescriptionView *edit;
    QAction *boldAction;
    QAction *italicAction;
    QAction *codeAction;
    QAction *bulletAction;
    QAction *imageAction;

    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void blockFormatButtonSignals(bool on);
};

#endif // RICHTEXTCONTROLLER_H
