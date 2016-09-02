#include "appsettingsdialog.h"
#include "ui_appsettingsdialog.h"

AppSettingsDialog::AppSettingsDialog(AppSettings *settings,
                                     QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppSettingsDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Application Settings"));

    this->settings = settings;
}

AppSettingsDialog::~AppSettingsDialog()
{
    delete ui;
}

int AppSettingsDialog::exec()
{
    ui->showIDsCheckBox->setChecked(settings->idIsVisible());
    return QDialog::exec();
}

void AppSettingsDialog::accept()
{
    settings->setIDVisible(ui->showIDsCheckBox->isChecked());
    QDialog::accept();
}
