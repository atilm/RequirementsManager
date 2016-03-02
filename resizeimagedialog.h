#ifndef RESIZEIMAGEDIALOG_H
#define RESIZEIMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class ResizeImageDialog;
}

class ResizeImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResizeImageDialog(QWidget *parent = 0);
    ~ResizeImageDialog();

private:
    Ui::ResizeImageDialog *ui;
};

#endif // RESIZEIMAGEDIALOG_H
