#include "descriptionview.h"
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QMimeData>
#include <QImageReader>
#include <QMessageBox>

DescriptionView::DescriptionView(RichTextResourceManager *resourcesManager,
                                 FileStateTracker *fileState,
                                 QWidget *parent) :
    QTextEdit(parent)
{
    defaultDocument = new QTextDocument();
    this->resourcesManager = resourcesManager;
    this->fileState = fileState;
    initialize();
}

void DescriptionView::setModel(RequirementsModel *data)
{
    this->data = data;
}

bool DescriptionView::canInsertFromMimeData(const QMimeData *source) const
{
    return source->hasImage() || source->hasUrls() ||
            QTextEdit::canInsertFromMimeData(source);
}

void DescriptionView::insertFromMimeData(const QMimeData *source)
{
    if (source->hasImage())
    {
        static int i = 1;
        QUrl url(QString("dropped_image_%1").arg(i++));
        dropImage(url, qvariant_cast<QImage>(source->imageData()));
    }
    else if (source->hasUrls())
    {
        foreach (QUrl url, source->urls())
        {
            QFileInfo info(url.toLocalFile());
            if (QImageReader::supportedImageFormats().contains(info.suffix().toLower().toLatin1()))
                dropImage(url, QImage(info.filePath()));
            else
                dropTextFile(url);
        }
    }
    else
    {
        QTextEdit::insertFromMimeData(source);
    }
}

void DescriptionView::insertImage()
{
    if(document() == defaultDocument)
        return;

    QString file = QFileDialog::getOpenFileName(this, tr("Select an image"),
                                                fileState->toAbsoluteFilePath("."),
                                                tr("Bitmap Files (*.bmp)\n"
                                                   "JPEG (*.jpg *jpeg)\n"
                                                   "GIF (*.gif)\n"
                                                   "PNG (*.png)\n"));

    try{
        resourcesManager->setDocument(document());
        QTextImageFormat imageFormat = resourcesManager->insertImage(file);
        //textCursor().insertImage(imageFormat);
    }
    catch(...){
        QMessageBox::information(this, tr("Error"), tr("Could not open file."));
    }
}

void DescriptionView::switchItem(const QModelIndex &current, const QModelIndex &previous)
{
    try{
        setDocument(data->getDescription(current));

        setEnabled(true);
    }
    catch(...){
        setDocument(defaultDocument);
        setDisabled(true);
    }
}

void DescriptionView::initialize()
{
    setDisabled(true);

    defaultDocument->setPlainText(tr("Click on the \"plus\" buttons to add requirements."));
    setDocument(defaultDocument);
}

void DescriptionView::dropImage(const QUrl &url, const QImage &image)
{
    if (!image.isNull()){
        document()->addResource(QTextDocument::ImageResource, url, image);
        textCursor().insertImage(url.toString());
    }
}

void DescriptionView::dropTextFile(const QUrl &url)
{
    QFile file(url.toLocalFile());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        textCursor().insertText(file.readAll());
}

