#ifndef QMESSAGEBOXPROVIDER_H
#define QMESSAGEBOXPROVIDER_H

#include <QWidget>
#include <QMessageBox>
#include <QInputDialog>

class QMessageBoxProvider
{
public:
    QMessageBoxProvider();
    virtual ~QMessageBoxProvider();

    //! Shows a QMessageBox with an info icon.
    /*!
    \param parent The parent widget.
    \param title The title of the message box.
    \param text The text in the message box.
    */
    virtual void showInfoBox(QWidget *parent, QString &title, QString &text);

    //! Shows a QMessageBox with a warning icon.
    /*!
    \param parent The parent widget.
    \param title The title of the message box.
    \param text The text in the message box.
    */
    virtual void showWarning(QWidget *parent, QString &title, QString &text);

    virtual QMessageBox::StandardButton showQuestion(QWidget *parent, QString &title, QString &text);

    //! Shows a DialogBox that requests the user to enter a double value.
    /*!
    \param parent The parent widget.
    \param title The dialog title.
    \param label The dialog text.
    \param value The initial value in the data entry field.
    \param min The minimum value that is accepted.
    \param max The maximum value that is accepted.
    \param decimals The number of decimal places to display.
    \param [out] ok Set to true, if user pressed OK. Set to false, if user pressed Cancel.
    \returns The entered double value.
    */
    virtual double getDouble(QWidget *parent, const QString &title,
                           const QString &label, double value = 0,
                           double min = -2147483647, double max = 2147483647,
                           int decimals = 1, bool *ok = 0);
};

#endif // QMESSAGEBOXPROVIDER_H
