#ifndef DESCRIPTIONVIEW_H
#define DESCRIPTIONVIEW_H

#include <QTextEdit>
#include "htmlgenerator.h"
#include "requirementsmodel.h"
#include "richtextresourcemanager.h"
#include "filestatetracker.h"
#include "resizeimagedialog.h"

class DescriptionView : public QTextEdit
{
    Q_OBJECT
public:
    explicit DescriptionView(RichTextResourceManager *resourcesManager,
                             FileStateTracker *fileState,
                             ResizeImageDialog *resizeDialog,
                             QWidget *parent = 0);

    void setModel(RequirementsModel *data);
    bool canInsertFromMimeData(const QMimeData *source) const;
    void insertFromMimeData(const QMimeData* source);

signals:

public slots:

    void insertImage();
    void switchItem(const QModelIndex &current, const QModelIndex &previous);
    void showItem(const QModelIndex &index);

protected:
    RichTextResourceManager *resourcesManager;
    FileStateTracker *fileState;
    QTextDocument *defaultDocument;
    RequirementsModel *data;
    ResizeImageDialog *resizeDialog;

    void initialize();
    void dropImage(const QImage &image);

    void mouseDoubleClickEvent(QMouseEvent *e);
    void resizeImage(QTextImageFormat format);
};

#endif // DESCRIPTIONVIEW_H