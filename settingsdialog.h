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
                            QWidget *parent = 0);
    virtual ~SettingsDialog();

private:
    Ui::SettingsDialog *ui;
    ProjectFileController *project;
    SourceCodeReaderProvider *readers;
    DirectoryListModel *sourceDirectories;
    DirectoryListModel *testDirectories;

    void initialize();
};

#endif // SETTINGSDIALOG_H
