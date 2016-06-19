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

void TestNode::appendToShortDescription(const QString &s)
{
    shortDescription += QString(" %1").arg(s);
}

void TestNode::appendToPreparation(const QString &s)
{
    preparation += s + "\n";
}

void TestNode::appendToAction(const QString &s)
{
    action += s + "\n";
}

void TestNode::appendToResult(const QString &s)
{
    expectedResult += s + "\n";
}

QString TestNode::getTestCase() const
{
    return testCase;
}

QString TestNode::getTestName() const
{
    return testName;
}

QString TestNode::getShortDescription() const
{
    return shortDescription;
}

QString TestNode::getPreparation() const
{
    return preparation;
}

QString TestNode::getAction() const
{
    return action;
}

QString TestNode::getExpectedResult() const
{
    return expectedResult;
}

