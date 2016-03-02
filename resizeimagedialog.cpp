#include "resizeimagedialog.h"
#include "ui_resizeimagedialog.h"

ResizeImageDialog::ResizeImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResizeImageDialog)
{
    ui->setupUi(this);
}

ResizeImageDialog::~ResizeImageDialog()
{
    delete ui;
}
