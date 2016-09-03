#ifndef PREVENTIVEACTIONDIALOG_H
#define PREVENTIVEACTIONDIALOG_H

#include <QDialog>
#include "preventiveactionmodel.h"
#include "qlineeditadapter.h"
#include "qplaintexteditadapter.h"

namespace Ui {
class PreventiveActionDialog;
}

class PreventiveActionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreventiveActionDialog(QWidget *parent = 0);
    ~PreventiveActionDialog();

    void injectWidgets(QLineEditAdapter *testCaseEdit,
                       QLineEditAdapter *testNameEdit,
                       QLineEditAdapter *shortDescriptionEdit,
                       QPlainTextEditAdapter *preparationEdit,
                       QPlainTextEditAdapter *actionEdit,
                       QPlainTextEditAdapter *expectedResultEdit);

    void setModel(shared_ptr<PreventiveActionModel> model);

public slots:
    virtual int exec(const QModelIndex &index);
    virtual void accept();

private:
    Ui::PreventiveActionDialog *ui;
    QLineEditAdapter *testCaseEdit;
    QLineEditAdapter *testNameEdit;
    QLineEditAdapter *shortDescriptionEdit;
    QPlainTextEditAdapter *preparationEdit;
    QPlainTextEditAdapter *actionEdit;
    QPlainTextEditAdapter *expectedResultEdit;

    shared_ptr<PreventiveActionModel> model;
    shared_ptr<PreventiveAction> currentAction;

    void setCurrentIndex(const QModelIndex &index);
};

#endif // PREVENTIVEACTIONDIALOG_H
