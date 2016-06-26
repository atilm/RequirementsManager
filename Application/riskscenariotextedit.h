#ifndef RISKSCENARIOTEXTEDIT_H
#define RISKSCENARIOTEXTEDIT_H

#include "qplaintexteditadapter.h"

class RiskScenarioTextEdit : public QPlainTextEditAdapter
{
public:
    RiskScenarioTextEdit(QWidget *parent = 0);
    virtual ~RiskScenarioTextEdit();

    virtual void keyPressEvent(QKeyEvent *e);
};

#endif // RISKSCENARIOTEXTEDIT_H
