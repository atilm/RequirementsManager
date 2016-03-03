#include "resizeimagedialog.h"
#include "ui_resizeimagedialog.h"
#include <QDebug>

ResizeImageDialog::ResizeImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResizeImageDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Resize image"));

    connect(ui->widthSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(handleWidthChanged(int)));
    connect(ui->heightSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(handleHeightChanged(int)));
}

ResizeImageDialog::~ResizeImageDialog()
{
    delete ui;
}

void ResizeImageDialog::setImageFormat(QTextImageFormat format,
                                       QTextDocument *document)
{
    ui->widthSpinBox->blockSignals(true);
    ui->heightSpinBox->blockSignals(true);

    if(format.width() == 0 || format.height() == 0)
        setWidthFromResource(format, document);
    else{
        ui->widthSpinBox->setValue(format.width());
        ui->heightSpinBox->setValue(format.height());
    }

    startWidth = ui->widthSpinBox->value();
    startHeight = ui->heightSpinBox->value();

    ui->widthSpinBox->blockSignals(false);
    ui->heightSpinBox->blockSignals(false);
}

int ResizeImageDialog::getImageWidth() const
{
    return ui->widthSpinBox->value();
}

int ResizeImageDialog::getImageHeight() const
{
    return ui->heightSpinBox->value();
}

void ResizeImageDialog::handleWidthChanged(int value)
{
    int newHeight = qRound(startHeight * (float)value / startWidth);
    ui->heightSpinBox->blockSignals(true);
    ui->heightSpinBox->setValue(newHeight);
    ui->heightSpinBox->blockSignals(false);
}

void ResizeImageDialog::handleHeightChanged(int value)
{
    int newWidth = qRound(startWidth * (float)value / startHeight);
    ui->widthSpinBox->blockSignals(true);
    ui->widthSpinBox->setValue(newWidth);
    ui->widthSpinBox->blockSignals(false);
}

void ResizeImageDialog::setWidthFromResource(QTextImageFormat format,
                                             QTextDocument *document)
{
    QImage img = document->resource(QTextDocument::ImageResource,
                                    format.name()).value<QImage>();

    ui->widthSpinBox->setValue(img.width());
    ui->heightSpinBox->setValue(img.height());
}
