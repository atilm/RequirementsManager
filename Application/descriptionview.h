#ifndef DESCRIPTIONVIEW_H
#define DESCRIPTIONVIEW_H

#include <QTextEdit>
#include "htmlgenerator.h"
#include "requirementsmodel.h"
#include "richtextresourcemanager.h"
#include "filestatetracker.h"
#include "resizeimagedialog.h"

#include <memory>
using namespace std;

class DescriptionView : public QTextEdit
{
    Q_OBJECT
public:
    explicit DescriptionView(RichTextResourceManager *resourcesManager,
                             FileStateTracker *fileState,
                             ResizeImageDialog *resizeDialog,
                             QWidget *parent = 0);

    void setModel(shared_ptr<RequirementsModel> data);
    bool canInsertFromMimeData(const QMimeData *source) const;
    void insertFromMimeData(const QMimeData* source);

signals:
    void readOnlyToggled(bool);

public slots:

    void insertImage();
    void switchItem(const QModelIndex &current, const QModelIndex &previous);
    void showItem(const QModelIndex &index);
    void setReadOnly(bool on);

protected:
    RichTextResourceManager *resourcesManager;
    FileStateTracker *fileState;
    QTextDocument *defaultDocument;
    shared_ptr<RequirementsModel> data;
    ResizeImageDialog *resizeDialog;

    void initialize();
    void dropImage(const QImage &image);

    void mouseDoubleClickEvent(QMouseEvent *e);
    void resizeImage(QTextImageFormat format);
};

#endif // DESCRIPTIONVIEW_H
