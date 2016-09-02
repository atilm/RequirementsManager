#ifndef APPSETTINGSDIALOG_H
#define APPSETTINGSDIALOG_H

#include "appsettings.h"

#include <QDialog>

namespace Ui {
class AppSettingsDialog;
}

class AppSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AppSettingsDialog(AppSettings *settings,
                               QWidget *parent = 0);
    ~AppSettingsDialog();

    virtual int exec();

public slots:
    virtual void accept();

private:
    Ui::AppSettingsDialog *ui;
    AppSettings *settings;

};

#endif // APPSETTINGSDIALOG_H
