#include "automatedtestreference.h"
#include "sourcecodecontroller.h"
#include <QDebug>

AutomatedTestReference::AutomatedTestReference(SourceAddress address,
                                               SourceCodeController *controller,
                                               shared_ptr<FileStateTracker> fileState)
    : PreventiveAction(fileState)
{
    this->address = address;
    this->controller = controller;

    testCase = address.testCase;
    testName = address.testName;

    node = nullptr;
    unresolvedMessage = "Unresolved test reference";
}

AutomatedTestReference::~AutomatedTestReference()
{

}

bool AutomatedTestReference::isReference() const
{
    return true;
}

SourceAddress AutomatedTestReference::getAddress() const
{
    return address;
}


QString AutomatedTestReference::getTestCase()
{
    return address.testCase;
}

QString AutomatedTestReference::getTestName()
{
    return address.testName;
}

QString AutomatedTestReference::getShortDescription()
{
    if(assertNodeResolved())
        return node->getShortDescription();
    else
        return unresolvedMessage;
}

QString AutomatedTestReference::getPreparation()
{
    if(assertNodeResolved())
        return node->getPreparation();
    else
        return QString();
}

QString AutomatedTestReference::getAction()
{
    if(assertNodeResolved())
        return node->getAction();
    else
        return QString();
}

QString AutomatedTestReference::getExpectedResult()
{
    if(assertNodeResolved())
        return node->getExpectedResult();
    else
        return QString();
}

bool AutomatedTestReference::assertNodeResolved()
{
    try{
        if(!node)
            node = controller->getTestNode(address);
        return true;
    }
    catch(const runtime_error &e){
        qDebug() << "Could not resolve test address";
        return false;
    }
}

