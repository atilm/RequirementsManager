#ifndef PREVENTIVEACTION_H
#define PREVENTIVEACTION_H

#include <QString>
#include "filestatetracker.h"

class PreventiveAction
{
public:
    PreventiveAction(FileStateTracker *fileState);
    virtual ~PreventiveAction();

    virtual QString getShortAction() const;

    virtual void setTestCase(const QString &testCase);
    virtual void setTestName(const QString &testName);
    virtual void setShortDescription(const QString &description);
    virtual void setPreparation(const QString &preparation);
    virtual void setAction(const QString &action);
    virtual void setExpectedResult(const QString &expectedResult);

    // The following functions are not const to make
    // them match their counterparts in the derived
    // class AutomatedTestReference which cannot be
    // const:
    virtual QString getTestCase();
    virtual QString getTestName();
    virtual QString getShortDescription();
    virtual QString getPreparation();
    virtual QString getAction();
    virtual QString getExpectedResult();

protected:
    FileStateTracker *fileState;
    QString testCase;
    QString testName;
    QString shortDescription;
    QString preparation;
    QString action;
    QString expectedResult;
};

#endif // PREVENTIVEACTION_H
