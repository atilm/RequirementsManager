#include "testnode.h"

TestNode::TestNode()
{

}

TestNode::~TestNode()
{

}

QString TestNode::getName() const
{
    return QString("%1::%2").arg(testCase).arg(testName);
}

void TestNode::setTestCase(const QString &s)
{
    testCase = s;
}

void TestNode::setTestName(const QString &s)
{
    testName = s;
}

void TestNode::appendToPreparation(const QString &s)
{
    preparation += s;
}

void TestNode::appendToAction(const QString &s)
{
    action += s;
}

void TestNode::appendToResult(const QString &s)
{
    expectedResult += s;
}

