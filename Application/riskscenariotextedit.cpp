#include "riskscenariotextedit.h"

RiskScenarioTextEdit::RiskScenarioTextEdit(QWidget *parent)
    : QPlainTextEditAdapter(parent)
{

}

RiskScenarioTextEdit::~RiskScenarioTextEdit()
{

}

void RiskScenarioTextEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Return)
        insertPlainText("\n-> ");
    else
        QPlainTextEdit::keyPressEvent(e);
}

