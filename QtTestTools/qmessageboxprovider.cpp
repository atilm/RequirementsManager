#include "qmessageboxprovider.h"
#include <QMessageBox>

QMessageBoxProvider::QMessageBoxProvider()
{
}

QMessageBoxProvider::~QMessageBoxProvider()
{
}

void QMessageBoxProvider::showInfoBox(QWidget *parent,
                                      const QString &title,
                                      const QString &text)
{
    QMessageBox::information(parent, title, text);
}

void QMessageBoxProvider::showWarning(QWidget *parent,
                                      const QString &title,
                                      const QString &text)
{
    QMessageBox::warning(parent, title, text);
}

QMessageBox::StandardButton QMessageBoxProvider::showQuestion(QWidget *parent,
                                                              const QString &title,
                                                              const QString &text)
{
    return QMessageBox::question(parent, title, text, QMessageBox::Yes|QMessageBox::No);
}

double QMessageBoxProvider::getDouble(QWidget *parent, const QString &title,
                                     const QString &label, double value,
                                     double min, double max,
                                     int decimals, bool *ok)
{
    return QInputDialog::getDouble(parent, title, label, value, min, max, decimals, ok);
}
