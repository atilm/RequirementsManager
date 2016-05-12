#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "projectfilecontroller.h"
#include "sourcecodereaderprovider.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(SourceCodeReaderProvider *readers,
                            ProjectFileController *project,
                            AppSettings *settings,
                            QWidget *parent = 0);
    virtual ~SettingsDialog();

private slots:
    void handleAddSourceDir();
    void handleRemoveSourceDir();
    void handleAddTestDir();
    void handleRemoveTestDir();
    void handleLanguageSelectionChanged(const QString &value);
    void handleProjectsLanguageChanged(const QString &value);

private:
    Ui::SettingsDialog *ui;
    ProjectFileController *project;
    SourceCodeReaderProvider *readers;
    AppSettings *settings;
    DirectoryListModel *sourceDirectories;
    DirectoryListModel *testDirectories;

    void initialize();
    QString getRelativeDirectoryPath();
};

#endif // SETTINGSDIALOG_H
