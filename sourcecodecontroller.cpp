#include "sourcecodecontroller.h"
#include <QDebug>

SourceCodeController::SourceCodeController(ProjectFileController *project,
                                           SourceCodeReaderProvider *readerProvider,
                                           QObject *parent)
    : QObject(parent)
{
    this->readerProvider = readerProvider;
    this->project = project;
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

void SourceCodeController::parseProjectCode()
{
    try{
        ISourceCodeReader *reader = readerProvider->getReader(project->getProgrammingLanguage());
        model = reader->parseSourceCode(project->sourceDirModel(),
                                        project->testDirModel());

        moduleView->setModel(model);
        functionView->setModel(nullptr);
        testView->setModel(nullptr);
    }
    catch(const runtime_error &e){
        qDebug() << e.what();
    }
}


