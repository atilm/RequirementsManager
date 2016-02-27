#ifndef PREVENTIVEACTIONFACTORY_H
#define PREVENTIVEACTIONFACTORY_H

#include "filestatetracker.h"
#include "sourcecodecontroller.h"

class PreventiveActionFactory
{
public:
    PreventiveActionFactory(FileStateTracker *stateTracker,
                            SourceCodeController *controller);
    virtual ~PreventiveActionFactory();

    virtual PreventiveAction* newPreventiveAction();
    virtual AutomatedTestReference* newTestReference(SourceAddress address);

private:
    FileStateTracker *fileState;
    SourceCodeController *controller;
};

#endif // PREVENTIVEACTIONFACTORY_H
