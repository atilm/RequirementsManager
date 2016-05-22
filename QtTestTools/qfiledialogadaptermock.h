#ifndef QFILEDIALOGADAPTERMOCK_H
#define QFILEDIALOGADAPTERMOCK_H

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "qfiledialogadapter.h"

class QFileDialogAdapterMock : public QFileDialogAdapter
{
public: 
    MOCK_METHOD3(getExistingDirectory, QString (QWidget *parent, const QString &caption, const QString &dir));
    MOCK_METHOD5(getOpenFileName, QString (QWidget *parent, const QString &caption, const QString &dir, const QString &filter, QString *selectedFilter));
    MOCK_METHOD5(getSaveFileName, QString (QWidget *parent, const QString &caption, const QString &dir, const QString &filter, QString *selectedFilter));
};

#endif // QFILEDIALOGADAPTERMOCK_H
