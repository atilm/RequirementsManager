#include "projectfilecontroller.h"

ProjectFileController::ProjectFileController(QFileDialogAdapter *fileDialog,
                                             QFileAdapter *file,
                                             ProjectFileReader *reader,
                                             ProjectFileWriter *writer) : QObject()
{
    model = NULL;

    this->dialogProvider = fileDialog;
    this->projectFile = file;
    this->reader = reader;
    this->writer = writer;
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
