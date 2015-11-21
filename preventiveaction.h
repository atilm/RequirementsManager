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

    void setTestCase(const QString &testCase);
    void setTestName(const QString &testName);
    void setShortDescription(const QString &description);
    void setPreparation(const QString &preparation);
    void setAction(const QString &action);
    void setExpectedResult(const QString &expectedResult);

    QString getTestCase() const;
    QString getTestName() const;
    QString getShortDescription() const;
    QString getPreparation() const;
    QString getAction() const;
    QString getExpectedResult() const;

private:
    FileStateTracker *fileState;
    QString testCase;
    QString testName;
    QString shortDescription;
    QString preparation;
    QString action;
    QString expectedResult;
};

#endif // PREVENTIVEACTION_H
