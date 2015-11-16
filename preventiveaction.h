#ifndef PREVENTIVEACTION_H
#define PREVENTIVEACTION_H

#include <QString>

class PreventiveAction
{
public:
    PreventiveAction();
    virtual ~PreventiveAction();

    virtual QString getShortAction() const;

    void setTestCase(const QString &testCase);
    void setTestName(const QString &testName);
    void setShortDescription(const QString &description);
    void setPreparation(const QString &preparation);
    void setAction(const QString &action);
    void setExpectedResult(const QString &expectedResult);

    QString getTestCase();
    QString getTestName();
    QString getShortDescription();
    QString getPreparation();
    QString getAction();
    QString getExpectedResult();

private:
    QString testCase;
    QString testName;
    QString shortDescription;
    QString preparation;
    QString action;
    QString expectedResult;
};

#endif // PREVENTIVEACTION_H
