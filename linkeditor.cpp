#include "linkeditor.h"
#include "ui_linkeditor.h"

LinkTypeEditor::LinkTypeEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinkEditor)
{
    ui->setupUi(this);
    setWindowTitle(tr("Edit link types"));
}

LinkTypeEditor::~LinkTypeEditor()
{
    delete ui;
}
