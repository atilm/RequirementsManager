#include "sourcecodecontroller.h"

SourceCodeController::SourceCodeController(QObject *parent) : QObject(parent)
{

}

SourceCodeController::~SourceCodeController()
{

}

void SourceCodeController::injectViews(QListView *moduleView,
                                       QListView *functionView,
                                       QListView *testView)
{
    this->moduleView = moduleView;
    this->functionView = functionView;
    this->testView = testView;
}


