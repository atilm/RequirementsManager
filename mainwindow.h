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
#include "appsettings.h"
#include "attributeeditor.h"
#include "riskdescriptionview.h"
#include "risktableview.h"
#include "preventiveactiontableview.h"

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
                        AppSettings *settings,
                        AttributeEditor *attributeDialog,
                        QWidget *parent = 0);
    ~MainWindow();

    void injectViews(RequirementsView *requirementsView,
                     DescriptionView *descriptionView);
    void injectRiskViews(RiskDescriptionView *riskDescriptionView,
                         RiskTableView *riskTableView,
                         PreventiveActionTableView *preventiveActionTableView);

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
    AppSettings *settings;
    AttributeEditor *attributeDialog;
    RiskDescriptionView *riskDescriptionView;
    RiskTableView *riskTableView;
    PreventiveActionTableView *preventiveActionTableView;

    void closeEvent(QCloseEvent *);

private slots:
    void handleFilePathChanged(const QString &fPath);
    void handleChangedStateChanged(bool unsavedChanges);
    void handleEditAttributes();
};

#endif // MAINWINDOW_H
