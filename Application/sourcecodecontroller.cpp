#include "sourcecodecontroller.h"
#include "automatedtestreference.h"
#include <QDebug>
#include <QMessageBox>

SourceCodeController::SourceCodeController(QFileSystemWatcher *fileWatcher,
                                           shared_ptr<FileStateTracker> stateTracker,
                                           ProjectFileController *project,
                                           SourceCodeReaderProvider *readerProvider,
                                           HtmlGenerator *htmlGenerator,
                                           QObject *parent)
    : QObject(parent)
{
    this->fileWatcher = fileWatcher;
    this->stateTracker = stateTracker;
    this->readerProvider = readerProvider;
    this->project = project;
    this->htmlGenerator = htmlGenerator;
    model = nullptr;
    parentWindow = nullptr;
    handlingFile = false;
}

SourceCodeController::~SourceCodeController()
{
    delete model;
}

void SourceCodeController::injectViews(QListView *moduleView,
                                       QListView *functionView,
                                       QListView *testView)
{
    this->moduleView = moduleView;
    this->functionView = functionView;
    this->testView = testView;
}

void SourceCodeController::injectMainWindow(QWidget *parentWindow)
{
    this->parentWindow = parentWindow;
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

QTextDocument* SourceCodeController::getDescription(SourceAddress address)
{
    QString html = htmlGenerator->toHtml(model->getDescription(address),
                                         HtmlGenerator::FIRST_LINE);
    description.setHtml(html);
    return &description;
}

TestNode *SourceCodeController::getTestNode(SourceAddress address)
{
    return model->getTestNode(address);
}

void SourceCodeController::parseProjectCode()
{
    delete model;
    model = nullptr;

    if(project->getProgrammingLanguage() == QString("None"))
        return;

    try{
        ISourceCodeReader *reader = readerProvider->getReader(project->getProgrammingLanguage());

        disconnect(fileWatcher, 0, this, 0);
        fileWatcher->removePaths(fileWatcher->files());

        model = reader->parseSourceCode(project->sourceDirModel(),
                                        project->testDirModel());

        fileWatcher->addPaths(reader->getFilePaths());
        connect(fileWatcher, SIGNAL(fileChanged(QString)),
                this, SLOT(handleFileChanged()));

        moduleView->setModel(model);
        functionView->setModel(nullptr);
        testView->setModel(nullptr);

        disconnectAllViewSlots();

        connect(moduleView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                this, SLOT(handleClassSelectionChanged(QModelIndex, QModelIndex)));
        connect(moduleView, SIGNAL(doubleClicked(QModelIndex)),
                this, SLOT(handleClassOrFunctionDoubleClicked(QModelIndex)));
        connect(moduleView, SIGNAL(clicked(QModelIndex)),
                this, SLOT(handleClassClicked(QModelIndex)));
    }
    catch(const runtime_error &e){
        qDebug() << e.what();
    }
}

void SourceCodeController::handleClassSelectionChanged(const QModelIndex &current,
                                                       const QModelIndex &)
{
    if(functionView->model() == nullptr){
        functionView->setModel(model);
        connect(functionView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                this, SLOT(handleFunctionSelectionChanged(QModelIndex,QModelIndex)));
        connect(functionView, SIGNAL(doubleClicked(QModelIndex)),
                this, SLOT(handleClassOrFunctionDoubleClicked(QModelIndex)));
        connect(functionView, SIGNAL(clicked(QModelIndex)),
                this, SLOT(handleFunctionClicked(QModelIndex)));
    }

    testView->setModel(nullptr);
    disconnectTestView();

    showDescription(current);
    functionView->setRootIndex(current);
}

void SourceCodeController::handleFunctionSelectionChanged(const QModelIndex &current,
                                                          const QModelIndex &)
{
    if(testView->model() == nullptr){
        testView->setModel(model);
        connect(testView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                this, SLOT(handleTestSelectionChanged(QModelIndex,QModelIndex)));
        connect(testView, SIGNAL(doubleClicked(QModelIndex)),
                this, SLOT(handleTestDoubleClicked(QModelIndex)));
        connect(testView, SIGNAL(clicked(QModelIndex)),
                this, SLOT(handleTestClicked(QModelIndex)));
    }

    showDescription(current);
    testView->setRootIndex(current);
}

void SourceCodeController::handleTestSelectionChanged(const QModelIndex &current,
                                                      const QModelIndex &)
{
    showTestDescription(current);
}

void SourceCodeController::handleClassClicked(const QModelIndex &index)
{
    if(index.isValid())
        handleClassSelectionChanged(index, QModelIndex());
}

void SourceCodeController::handleFunctionClicked(const QModelIndex &index)
{
    if(index.isValid())
        handleFunctionSelectionChanged(index, QModelIndex());
}

void SourceCodeController::handleTestClicked(const QModelIndex &index)
{
    if(index.isValid())
        handleTestSelectionChanged(index, QModelIndex());
}

void SourceCodeController::handleClassOrFunctionDoubleClicked(const QModelIndex &index)
{
    SourceAddress address = model->getAddress(index);
    reqView->appendChild(reqFactory->newDesignReference(address));
}

void SourceCodeController::handleTestDoubleClicked(const QModelIndex &index)
{
    auto testRef = make_shared<AutomatedTestReference>(model->getAddress(index),
                                                       this,
                                                       stateTracker);

    preventiveActionView->appendTestReference(testRef);
}

void SourceCodeController::handleFileChanged()
{
    /* The QFileSystemWatcher emits several fileChanged signals
     * when a file has been modified. The handling file variable
     * is introduced to react only once to such a series of signals.
     */
    if(handlingFile)
        return;

    handlingFile = true;
    QMessageBox::StandardButton answer = QMessageBox::question(parentWindow,
                                                               tr("Source file changed"),
                                                               tr("Reload the source files now?"));

    if(answer == QMessageBox::Yes){
        parseProjectCode();
    }
    handlingFile = false;
}

void SourceCodeController::showDescription(const QModelIndex &index)
{
    SourceAddress address = model->getAddress(index);
    functionSpecView->setDocument(getDescription(address));
    functionSpecView->setEnabled(true);
    functionSpecView->setReadOnly(true);
}

void SourceCodeController::showTestDescription(const QModelIndex &index)
{
    try{
        testSpecView->displayTestReference(model->getTestNode(index));
    }
    catch(const runtime_error &e){

    }
}

void SourceCodeController::disconnectAllViewSlots()
{
    disconnect(moduleView->selectionModel(), 0, this, 0);
    disconnect(moduleView, 0, this, 0);
    disconnectFunctionView();
    disconnectTestView();
}

void SourceCodeController::disconnectFunctionView()
{
    disconnect(functionView->selectionModel(), 0, this, 0);
    disconnect(functionView, 0, this, 0);
}

void SourceCodeController::disconnectTestView()
{
    disconnect(testView->selectionModel(), 0, this, 0);
    disconnect(testView, 0, this, 0);
}


