#ifndef TESTNAMELINEEDIT_H
#define TESTNAMELINEEDIT_H

#include "qlineeditadapter.h"

class TestNameLineEdit : public QLineEditAdapter
{
public:
    TestNameLineEdit(QWidget *parent = 0);
    virtual ~TestNameLineEdit();

    virtual void keyPressEvent(QKeyEvent *e);
};

#endif // TESTNAMELINEEDIT_H
