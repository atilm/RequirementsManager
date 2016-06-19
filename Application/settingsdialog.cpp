#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QFileDialog>

SettingsDialog::SettingsDialog(SourceCodeReaderProvider *readers,
                               ProjectFileController *project,
                               AppSettings *settings,
                               QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->project = project;
    this->readers = readers;
    this->settings = settings;

    sourceDirectories = project->sourceDirModel();
    testDirectories = project->testDirModel();

    ui->sourceDirsListView->setModel(sourceDirectories);
    ui->testDirsListView->setModel(testDirectories);

    initialize();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

int SettingsDialog::exec()
{
    setUnchanged();

    return QDialog::exec();
}

void SettingsDialog::handleAddSourceDir()
{
    QString dir = getRelativeDirectoryPath();

    if(!dir.isEmpty()){
        sourceDirectories->add(dir);
        setChanged();
    }
}

void SettingsDialog::handleRemoveSourceDir()
{
    bool success = sourceDirectories->remove(ui->sourceDirsListView
                                             ->selectionModel()->currentIndex());

    if(success)
        setChanged();
}

void SettingsDialog::handleAddTestDir()
{
    QString dir = getRelativeDirectoryPath();

    if(!dir.isEmpty()){
        testDirectories->add(dir);
        setChanged();
    }
}

void SettingsDialog::handleRemoveTestDir()
{
    bool success = testDirectories->remove(ui->testDirsListView
                                           ->selectionModel()->currentIndex());

    if(success)
        setChanged();
}

void SettingsDialog::handleLanguageSelectionChanged(const QString &value)
{
    project->setProgrammingLanguage(value);
    setChanged();
}

void SettingsDialog::handleProjectsLanguageChanged(const QString &value)
{
    int lastIndex = ui->languageComboBox->count() - 1;

    for(int i=0; i < lastIndex; i++){
        if(ui->languageComboBox->itemText(i) == value){
            ui->languageComboBox->setCurrentIndex(i);
            return;
        }
    }

    ui->languageComboBox->setCurrentIndex(lastIndex);
}

void SettingsDialog::initialize()
{
    ui->languageComboBox->clear();

    foreach (QString name, readers->availableLanguages()) {
        ui->languageComboBox->addItem(name);
    }
    ui->languageComboBox->addItem("None");
    project->setProgrammingLanguage("None");

    ui->languageComboBox->setCurrentText(project->getProgrammingLanguage());

    connect(project, SIGNAL(programmingLanguageChanged(QString)),
            this, SLOT(handleProjectsLanguageChanged(QString)));
    connect(ui->addSourceDirButton, SIGNAL(clicked(bool)),
            this, SLOT(handleAddSourceDir()));
    connect(ui->removeSourceDirButton, SIGNAL(clicked(bool)),
            this, SLOT(handleRemoveSourceDir()));
    connect(ui->addTestDirButton, SIGNAL(clicked(bool)),
            this, SLOT(handleAddTestDir()));
    connect(ui->removeTestDirButton, SIGNAL(clicked(bool)),
            this, SLOT(handleRemoveTestDir()));
    connect(ui->languageComboBox, SIGNAL(currentTextChanged(QString)),
            this, SLOT(handleLanguageSelectionChanged(QString)));

    setUnchanged();
}

QString SettingsDialog::getRelativeDirectoryPath()
{
    QString dir = QFileDialog::getExistingDirectory(0,
                                                    "Choose source code directory",
                                                    settings->directory());
    if(!dir.isEmpty()){
        QDir root(settings->directory());
        return root.relativeFilePath(dir);
    }
    else
        return QString();
}

void SettingsDialog::setUnchanged()
{
    unsavedChanges = false;
}

void SettingsDialog::setChanged()
{
    unsavedChanges = true;
}

void SettingsDialog::reject()
{
    if(unsavedChanges)
        emit settingsChanged();

    QDialog::reject();
}
