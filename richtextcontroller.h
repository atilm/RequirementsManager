#ifndef RICHTEXTCONTROLLER_H
#define RICHTEXTCONTROLLER_H

#include <QTextEdit>
#include <QAction>

class RichTextController : QObject
{
    Q_OBJECT
public:
    RichTextController();

    virtual void setTextEdit(QTextEdit *edit);
    virtual void setBoldAction(QAction *boldAction);
    virtual void setItalicAction(QAction *italicAction);
    virtual void setBulletAction(QAction *bulletAction);

private:
    QTextEdit *edit;
    QAction *boldAction;
    QAction *italicAction;
    QAction *bulletAction;

private slots:
    void handleBoldToggled(bool on);
    void handleBulletToggled(bool on);
    void handleFormatChanged(QTextCharFormat format);
};

#endif // RICHTEXTCONTROLLER_H
