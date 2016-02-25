#include "preventiveaction.h"
#include <QObject>

PreventiveAction::PreventiveAction(FileStateTracker *fileState)
{
    this->fileState = fileState;
    testCase = "TestCase";
    testName = "TestName";
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
    if(testCase != this->testCase){
        this->testCase = testCase;
        fileState->setChanged(true);
    }
}

void PreventiveAction::setTestName(const QString &testName)
{
    if(testName != this->testName){
        this->testName = testName;
        fileState->setChanged(true);
    }
}

void PreventiveAction::setShortDescription(const QString &description)
{
    if(description != this->shortDescription){
        this->shortDescription = description;
        fileState->setChanged(true);
    }
}

void PreventiveAction::setPreparation(const QString &preparation)
{
    if(preparation != this->preparation){
        this->preparation = preparation;
        fileState->setChanged(true);
    }
}

void PreventiveAction::setAction(const QString &action)
{
    if(action != this->action){
        this->action = action;
        fileState->setChanged(true);
    }
}

void PreventiveAction::setExpectedResult(const QString &expectedResult)
{
    if(expectedResult != this->expectedResult){
        this->expectedResult = expectedResult;
        fileState->setChanged(true);
    }
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
