#include "sourcecodecontroller.h"

SourceCodeController::SourceCodeController(SourceCodeReaderProvider *readerProvider,
                                           QObject *parent)
    : QObject(parent)
{
    this->readerProvider = readerProvider;
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


