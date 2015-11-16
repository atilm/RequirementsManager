#include "preventiveaction.h"

PreventiveAction::PreventiveAction()
{
}

PreventiveAction::~PreventiveAction()
{

}

QString PreventiveAction::getShortAction() const
{
    return QString("%1::%2").arg(testCase).arg(testName);
}

void PreventiveAction::setTestCase(const QString &testCase)
{
    this->testCase = testCase;
}

void PreventiveAction::setTestName(const QString &testName)
{
    this->testName = testName;
}

void PreventiveAction::setShortDescription(const QString &description)
{
    this->shortDescription = description;
}

void PreventiveAction::setPreparation(const QString &preparation)
{
    this->preparation = preparation;
}

void PreventiveAction::setAction(const QString &action)
{
    this->action = action;
}

void PreventiveAction::setExpectedResult(const QString &expectedResult)
{
    this->expectedResult = expectedResult;
}

QString PreventiveAction::getTestCase()
{
    return testCase;
}

QString PreventiveAction::getTestName()
{
    return testName;
}

QString PreventiveAction::getShortDescription()
{
    return shortDescription;
}

QString PreventiveAction::getPreparation()
{
    return preparation;
}

QString PreventiveAction::getAction()
{
    return action;
}

QString PreventiveAction::getExpectedResult()
{
    return expectedResult;
}
