#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(SourceCodeReaderProvider *readers,
                               ProjectFileController *project,
                               QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->project = project;
    this->readers = readers;

    initialize();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::initialize()
{
    ui->languageComboBox->clear();

    foreach (QString name, readers->availableLanguages()) {
        ui->languageComboBox->addItem(name);
    }
}
