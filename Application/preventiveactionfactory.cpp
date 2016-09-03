#include "preventiveactionfactory.h"

PreventiveActionFactory::PreventiveActionFactory(shared_ptr<FileStateTracker> stateTracker,
                                                 SourceCodeController *controller)
{
    this->fileState = stateTracker;
    this->controller = controller;
}

PreventiveActionFactory::~PreventiveActionFactory()
{

}

shared_ptr<PreventiveAction> PreventiveActionFactory::newPreventiveAction()
{
    return make_shared<PreventiveAction>(fileState);
}

shared_ptr<AutomatedTestReference> PreventiveActionFactory::newTestReference(SourceAddress address)
{
    return make_shared<AutomatedTestReference>(address, controller, fileState);
}

