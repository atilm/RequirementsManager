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

        connect(this->moduleView->selectionModel(),
                SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                this,
                SLOT(handleClassSelectionChanged(QModelIndex, QModelIndex)));
    }
    catch(const runtime_error &e){
        qDebug() << e.what();
    }
}

void SourceCodeController::handleClassSelectionChanged(const QModelIndex &current,
                                                       const QModelIndex &previous)
{
    if(functionView->model() == nullptr){
        functionView->setModel(model);
        connect(this->functionView->selectionModel(),
                SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                this,
                SLOT(handleFunctionSelectionChanged(QModelIndex,QModelIndex)));
    }

    testView->setModel(nullptr);

    functionView->setRootIndex(current);
}

void SourceCodeController::handleFunctionSelectionChanged(const QModelIndex &current,
                                                          const QModelIndex &previous)
{
    if(testView->model() == nullptr)
        testView->setModel(model);

    testView->setRootIndex(current);
}


