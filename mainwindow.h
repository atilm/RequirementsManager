#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "richtextcontroller.h"
#include "requirementsview.h"
#include "descriptionview.h"
#include "requirementsmodel.h"
#include "projectfilecontroller.h"
#include "filestatetracker.h"
#include "qmessageboxprovider.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ProjectFileController *fileController,
                        RequirementsModel *requirements,
                        RichTextController *richText,
                        FileStateTracker *fileState,
                        QMessageBoxProvider *messageBox,
                        QWidget *parent = 0);
    ~MainWindow();

    void injectViews(RequirementsView *requirementsView,
                     DescriptionView *descriptionView);

private:
    QString applicationName;
    Ui::MainWindow *ui;
    RequirementsModel *requirements;
    RichTextController *richText;
    ProjectFileController *fileController;
    RequirementsView *requirementsView;
    DescriptionView *descriptionView;
    FileStateTracker *fileState;
    QMessageBoxProvider *messageBox;

    void closeEvent(QCloseEvent *);

private slots:
    void handleFilePathChanged(const QString &fPath);
    void handleChangedStateChanged(bool unsavedChanges);
};

#endif // MAINWINDOW_H
