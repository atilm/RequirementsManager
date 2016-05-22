#ifndef QFILEDIALOGADAPTER_H
#define QFILEDIALOGADAPTER_H

#include <QFileDialog>

class QFileDialogAdapter
{
public:
    QFileDialogAdapter();
    virtual ~QFileDialogAdapter();
    virtual QString getExistingDirectory(QWidget *parent=0,
                                          const QString &caption = QString(),
                                          const QString &dir = QString());

    virtual QString getOpenFileName(QWidget * parent=0,
                                    const QString &caption=QString(),
                                    const QString &dir = QString(),
                                    const QString &filter = QString(),
                                    QString *selectedFilter = 0);

    virtual QString getSaveFileName(QWidget * parent=0,
                                    const QString &caption=QString(),
                                    const QString &dir = QString(),
                                    const QString &filter = QString(),
                                    QString *selectedFilter = 0);
};

#endif // QFILEDIALOGADAPTER_H
