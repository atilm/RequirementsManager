#ifndef TESTNODE_H
#define TESTNODE_H

#include "sourcenode.h"

#include <QString>

class TestNode : public SourceNode
{
public:
    TestNode();
    virtual ~TestNode();

    virtual QString getName() const;
    void setTestCase(const QString &s);
    void setTestName(const QString &s);

    void appendToPreparation(const QString &s);
    void appendToAction(const QString &s);
    void appendToResult(const QString &s);

private:
    QString testCase;
    QString testName;

    QString preparation;
    QString action;
    QString expectedResult;
};

#endif // TESTNODE_H
