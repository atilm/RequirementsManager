#include "automatedtestreference.h"
#include "sourcecodecontroller.h"

AutomatedTestReference::AutomatedTestReference(SourceAddress address,
                                               SourceCodeController *controller,
                                               FileStateTracker *fileState)
    : PreventiveAction(fileState)
{
    this->address = address;
    this->controller = controller;

    node = nullptr;
    unresolvedMessage = "Unresolved test reference";
}

AutomatedTestReference::~AutomatedTestReference()
{

}

QString AutomatedTestReference::getTestCase() const
{
    return address.testCase;
}

QString AutomatedTestReference::getTestName() const
{
    return address.testName;
}

QString AutomatedTestReference::getShortDescription()
{
    if(assertNodeResolved())
        return node->getPreparation();
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
        return false;
    }
}

