#include "sourcecodecontroller.h"
#include "automatedtestreference.h"
#include <QDebug>

SourceCodeController::SourceCodeController(FileStateTracker *stateTracker,
                                           ProjectFileController *project,
                                           SourceCodeReaderProvider *readerProvider,
                                           QObject *parent)
    : QObject(parent)
{
    this->stateTracker = stateTracker;
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

void SourceCodeController::injectDescriptionView(DescriptionView *view)
{
    functionSpecView = view;
}

void SourceCodeController::injectRiskDescriptionView(RiskDescriptionView *view)
{
    testSpecView = view;
}

void SourceCodeController::injectRequirementsFactory(RequirementFactory *reqFactory)
{
    this->reqFactory = reqFactory;
}

void SourceCodeController::injectRequirementsView(RequirementsView *reqView)
{
    this->reqView = reqView;
}

void SourceCodeController::injectPreventiveActionView(PreventiveActionTableView *actionView)
{
    this->preventiveActionView = actionView;
}

QString SourceCodeController::getDescription(SourceAddress address)
{
    return model->getDescription(address);
}

TestNode *SourceCodeController::getTestNode(SourceAddress address)
{
    return model->getTestNode(address);
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

        connect(moduleView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                this, SLOT(handleClassSelectionChanged(QModelIndex, QModelIndex)));
        connect(moduleView, SIGNAL(doubleClicked(QModelIndex)),
                this, SLOT(handleClassOrFunctionDoubleClicked(QModelIndex)));
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
        connect(this->functionView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                this, SLOT(handleFunctionSelectionChanged(QModelIndex,QModelIndex)));
        connect(functionView, SIGNAL(doubleClicked(QModelIndex)),
                this, SLOT(handleClassOrFunctionDoubleClicked(QModelIndex)));
    }

    testView->setModel(nullptr);

    showDescription(current);
    functionView->setRootIndex(current);
}

void SourceCodeController::handleFunctionSelectionChanged(const QModelIndex &current,
                                                          const QModelIndex &previous)
{
    if(testView->model() == nullptr){
        testView->setModel(model);
        connect(testView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                this, SLOT(handleTestSelectionChanged(QModelIndex,QModelIndex)));
        connect(testView, SIGNAL(doubleClicked(QModelIndex)),
                this, SLOT(handleTestDoubleClicked(QModelIndex)));
    }

    showDescription(current);
    testView->setRootIndex(current);
}

void SourceCodeController::handleTestSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    showTestDescription(current);
}

void SourceCodeController::handleClassOrFunctionDoubleClicked(const QModelIndex &index)
{
    SourceAddress address = model->getAddress(index);
    reqView->appendChild(reqFactory->newDesignReference(address));
}

void SourceCodeController::handleTestDoubleClicked(const QModelIndex &index)
{
    AutomatedTestReference *testRef = new AutomatedTestReference(model->getAddress(index),
                                                                 this,
                                                                 stateTracker);
    preventiveActionView->appendTestReference(testRef);
}

void SourceCodeController::showDescription(const QModelIndex &index)
{
    document.setPlainText(model->getDescription(index));
    functionSpecView->setDocument(&document);
    functionSpecView->setEnabled(true);
}

void SourceCodeController::showTestDescription(const QModelIndex &index)
{
    try{
        testSpecView->displayTestReference(model->getTestNode(index));
    }
    catch(const runtime_error &e){

    }
}


