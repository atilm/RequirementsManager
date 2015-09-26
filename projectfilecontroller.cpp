#include "projectfilecontroller.h"

ProjectFileController::ProjectFileController(QFileDialogAdapter *fileDialog,
                                             QFileAdapter *file,
                                             ProjectFileReader *reader,
                                             ProjectFileWriter *writer,
                                             FileStateTracker *stateTracker,
                                             AppSettings *settings) : QObject()
{
    model = NULL;

    this->dialogProvider = fileDialog;
    this->projectFile = file;
    this->reader = reader;
    this->writer = writer;
    this->stateTracker = stateTracker;
    this->settings = settings;

    filterString = tr("Requirment Files (*.req)");
}

ProjectFileController::~ProjectFileController()
{
    delete dialogProvider;
    delete projectFile;
    delete reader;
    delete writer;
}

void ProjectFileController::setModel(RequirementsModel *model)
{
    this->model = model;
}

void ProjectFileController::save()
{
    QString currentPath = stateTracker->filePath();

    if(currentPath.isEmpty())
        saveAs();
    else{
        projectFile->setFileName(currentPath);
        writer->save(model, projectFile);
        stateTracker->setChanged(false);
    }
}

void ProjectFileController::saveAs()
{
    QString startDir = settings->directory();

    QString filePath = dialogProvider->getSaveFileName(0, tr("Save file"),
                                                       startDir, filterString);

    if(!filePath.isEmpty()){
        projectFile->setFileName(filePath);
        writer->save(model, projectFile);
        stateTracker->setFilePath(filePath);
        stateTracker->setChanged(false);
    }
}

void ProjectFileController::load()
{
    QString startDir = settings->directory();

    QString filePath = dialogProvider->getOpenFileName(0, tr("Open file"),
                                                       startDir, filterString);

    if(!filePath.isEmpty()){
        projectFile->setFileName(filePath);
        reader->load(model, projectFile);
        stateTracker->setFilePath(filePath);
        stateTracker->setChanged(false);
    }
}
