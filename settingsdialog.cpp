#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(ProjectFileController *project,
                               QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->project = project;
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
