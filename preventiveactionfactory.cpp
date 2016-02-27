#include "preventiveactionfactory.h"

PreventiveActionFactory::PreventiveActionFactory(FileStateTracker *stateTracker,
                                                 SourceCodeController *controller)
{
    this->fileState = stateTracker;
    this->controller = controller;
}

PreventiveActionFactory::~PreventiveActionFactory()
{

}

PreventiveAction *PreventiveActionFactory::newPreventiveAction()
{
    return new PreventiveAction(fileState);
}

AutomatedTestReference *PreventiveActionFactory::newTestReference(SourceAddress address)
{
    return new AutomatedTestReference(address, controller, fileState);
}

