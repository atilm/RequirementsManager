#ifndef RESIZEIMAGEDIALOG_H
#define RESIZEIMAGEDIALOG_H

#include <QDialog>
#include <QTextCharFormat>
#include <QTextDocument>

namespace Ui {
class ResizeImageDialog;
}

class ResizeImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResizeImageDialog(QWidget *parent = 0);
    ~ResizeImageDialog();

    void setImageFormat(QTextImageFormat format,
                        QTextDocument *document);
    int getImageWidth() const;
    int getImageHeight() const;

private:
    Ui::ResizeImageDialog *ui;
    float startWidth;
    float startHeight;

private slots:
    void handleWidthChanged(int value);
    void handleHeightChanged(int value);
    void setWidthFromResource(QTextImageFormat format,
                              QTextDocument *document);
};

#endif // RESIZEIMAGEDIALOG_H
