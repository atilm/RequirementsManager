#ifndef DESCRIPTIONVIEW_H
#define DESCRIPTIONVIEW_H

#include <QTextEdit>
#include "requirementsmodel.h"
#include "richtextresourcemanager.h"
#include "filestatetracker.h"

class DescriptionView : public QTextEdit
{
    Q_OBJECT
public:
    explicit DescriptionView(RichTextResourceManager *resourcesManager,
                             FileStateTracker *fileState,
                             QWidget *parent = 0);

    void setModel(RequirementsModel *data);
    bool canInsertFromMimeData(const QMimeData *source) const;
    void insertFromMimeData(const QMimeData* source);

signals:

public slots:

    void insertImage();
    void switchItem(const QModelIndex &current, const QModelIndex &previous);

private:
    RichTextResourceManager *resourcesManager;
    FileStateTracker *fileState;
    QTextDocument *defaultDocument;
    RequirementsModel *data;

    void initialize();
    void dropImage(const QUrl &url, const QImage &image);
    void dropTextFile(const QUrl &url);
};

#endif // DESCRIPTIONVIEW_H
