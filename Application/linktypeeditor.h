#ifndef LINKTYPEEDITOR_H
#define LINKTYPEEDITOR_H

#include <QDialog>

#include "linkcontext.h"

namespace Ui {
class LinkEditor;
}

class LinkTypeEditor : public QDialog
{
    Q_OBJECT

public:
    explicit LinkTypeEditor(LinkContext *context, QWidget *parent = 0);
    ~LinkTypeEditor();

private:
    Ui::LinkEditor *ui;
    LinkContext *context;

private slots:
    void handleAddClicked();
    void handleRemoveClicked();
    void handleRenameClicked();
    QString takeName();
};

#endif // LINKTYPEEDITOR_H
