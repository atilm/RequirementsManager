#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include "riskassessmentdialog.h"
#include "riskassessmenteditcontroller.h"
#include "linktypeeditor.h"
#include "linkcontroller.h"
#include "sourcecodecontroller.h"
#include "settingsdialog.h"
#include "reportcontroller.h"

#include <QMainWindow>

#include <memory>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ProjectFileController *fileController,
                        shared_ptr<RequirementsModel> requirements,
                        RichTextController *richText,
                        shared_ptr<FileStateTracker> fileState,
                        QMessageBoxProvider *messageBox,
                        AppSettings *settings,
                        AttributeEditor *attributeDialog,
                        RiskAssessmentEditController *riskAssessmentEditController,
                        LinkTypeEditor *linkTypeEditor,
                        LinkController *linkController,
                        SourceCodeController *sourceController,
                        SettingsDialog *settingsDialog,
                        ReportController *reportController,
                        QWidget *parent);
    ~MainWindow();

    void injectViews(RequirementsView *requirementsView,
                     DescriptionView *descriptionView);
    void injectRiskViews(RiskDescriptionView *riskDescriptionView,
                         RiskTableView *riskTableView,
                         PreventiveActionTableView *preventiveActionTableView);

private:
    QString applicationName;
    Ui::MainWindow *ui;
    shared_ptr<RequirementsModel> requirements;
    RichTextController *richText;
    ProjectFileController *fileController;
    RequirementsView *requirementsView;
    DescriptionView *descriptionView;
    shared_ptr<FileStateTracker> fileState;
    QMessageBoxProvider *messageBox;
    AppSettings *settings;
    AttributeEditor *attributeDialog;
    RiskDescriptionView *riskDescriptionView;
    RiskTableView *riskTableView;
    RiskAssessmentEditController *riskAssessmentEditController;
    PreventiveActionTableView *preventiveActionTableView;
    LinkTypeEditor *linkTypeEditor;
    LinkController *linkController;
    SourceCodeController *sourceController;
    SettingsDialog *settingsDialog;
    ReportController *reportController;

    void closeEvent(QCloseEvent *);

private slots:
    void handleFilePathChanged(const QString &fPath);
    void handleChangedStateChanged(bool unsavedChanges);
    void setSplitterBehaviour();
};

#endif // MAINWINDOW_H
