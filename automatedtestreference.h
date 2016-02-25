#ifndef AUTOMATEDTESTREFERENCE_H
#define AUTOMATEDTESTREFERENCE_H

#include "sourcecodemodel.h"
#include "preventiveaction.h"
#include "testnode.h"

class SourceCodeController;

class AutomatedTestReference : public PreventiveAction
{
public:
    AutomatedTestReference(SourceAddress address,
                           SourceCodeController *controller,
                           FileStateTracker *fileState);
    virtual ~AutomatedTestReference();

    QString getTestCase();
    QString getTestName();
    QString getShortDescription();
    QString getPreparation();
    QString getAction();
    QString getExpectedResult();

private:
    QString unresolvedMessage;
    TestNode *node;
    SourceAddress address;
    SourceCodeController *controller;

    bool assertNodeResolved();
};

#endif // AUTOMATEDTESTREFERENCE_H
