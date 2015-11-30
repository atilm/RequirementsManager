#ifndef LINKEDITOR_H
#define LINKEDITOR_H

#include <QDialog>

namespace Ui {
class LinkEditor;
}

class LinkTypeEditor : public QDialog
{
    Q_OBJECT

public:
    explicit LinkTypeEditor(QWidget *parent = 0);
    ~LinkTypeEditor();

private:
    Ui::LinkEditor *ui;
};

#endif // LINKEDITOR_H
