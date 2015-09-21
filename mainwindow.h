#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "richtextcontroller.h"
#include "requirementsview.h"
#include "descriptionview.h"
#include "requirementsmodel.h"
#include "projectfilecontroller.h"

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
                        QWidget *parent = 0);
    ~MainWindow();

    void injectViews(RequirementsView *requirementsView,
                     DescriptionView *descriptionView);

private:
    Ui::MainWindow *ui;
    RequirementsModel *requirements;
    RichTextController *richText;
    ProjectFileController *fileController;
    RequirementsView *requirementsView;
    DescriptionView *descriptionView;
};

#endif // MAINWINDOW_H
