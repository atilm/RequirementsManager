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

}

void ProjectFileController::saveAs()
{

}

void ProjectFileController::load()
{

}
