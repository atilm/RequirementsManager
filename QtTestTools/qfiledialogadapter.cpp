#include "qfiledialogadapter.h"

QFileDialogAdapter::QFileDialogAdapter()
{
}

QFileDialogAdapter::~QFileDialogAdapter()
{
}

QString QFileDialogAdapter::getExistingDirectory(QWidget *parent, const QString &caption, const QString &dir)
{
    return QFileDialog::getExistingDirectory(parent,
                                             caption,
                                             dir,
                                             QFileDialog::ShowDirsOnly);
}

QString QFileDialogAdapter::getOpenFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter, QString *selectedFilter)
{
    return QFileDialog::getOpenFileName(parent,
                                        caption,
                                        dir,
                                        filter,
                                        selectedFilter,
                                        0);
}

QString QFileDialogAdapter::getSaveFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter, QString *selectedFilter)
{
    return QFileDialog::getSaveFileName(parent,
                                        caption,
                                        dir,
                                        filter,
                                        selectedFilter,
                                        0);
}
