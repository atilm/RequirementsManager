#ifndef ATTRIBUTEEDITOR_H
#define ATTRIBUTEEDITOR_H

#include <QDialog>
#include "attributecontext.h"

namespace Ui {
class AttributeEditor;
}

class AttributeEditor : public QDialog
{
    Q_OBJECT

public:
    explicit AttributeEditor(AttributeContext *context, QWidget *parent = 0);
    virtual ~AttributeEditor();

private:
    Ui::AttributeEditor *ui;
    AttributeContext *context;

    void initTypeBox();

private slots:
    void handleAddClicked();
    void handleRemoveClicked();
};

#endif // ATTRIBUTEEDITOR_H
