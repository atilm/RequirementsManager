#ifndef QMESSAGEBOXPROVIDERMOCK_H
#define QMESSAGEBOXPROVIDERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "qmessageboxprovider.h"

class QMessageBoxProviderMock : public QMessageBoxProvider
{
public:
    MOCK_METHOD3(showInfoBox, void (QWidget *parent, QString &title, QString &text));
    MOCK_METHOD3(showWarning, void (QWidget *parent, QString &title, QString &text));
    MOCK_METHOD3(showQuestion, QMessageBox::StandardButton (QWidget *parent, QString &title, QString &text));
    MOCK_METHOD8(getDouble, double (QWidget *parent, const QString &title,
                                    const QString &label, double value,
                                    double min, double max,
                                    int decimals, bool *ok));

};

#endif // QMESSAGEBOXPROVIDERMOCK_H
