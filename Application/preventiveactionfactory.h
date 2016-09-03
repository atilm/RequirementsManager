#ifndef PREVENTIVEACTIONFACTORY_H
#define PREVENTIVEACTIONFACTORY_H

#include "filestatetracker.h"
#include "sourcecodecontroller.h"

class PreventiveActionFactory
{
public:
    PreventiveActionFactory(shared_ptr<FileStateTracker> stateTracker,
                            SourceCodeController *controller);
    virtual ~PreventiveActionFactory();

    virtual shared_ptr<PreventiveAction> newPreventiveAction();
    virtual shared_ptr<AutomatedTestReference> newTestReference(SourceAddress address);

private:
    shared_ptr<FileStateTracker> fileState;
    SourceCodeController *controller;
};

#endif // PREVENTIVEACTIONFACTORY_H
