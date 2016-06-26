#include "testnamelineedit.h"
#include <QKeyEvent>

TestNameLineEdit::TestNameLineEdit(QWidget *parent)
    : QLineEditAdapter(parent)
{

}

TestNameLineEdit::~TestNameLineEdit()
{

}

void TestNameLineEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Space)
        insert("_");
    else
        QLineEdit::keyPressEvent(e);
}

