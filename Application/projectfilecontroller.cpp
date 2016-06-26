#include "projectfilecontroller.h"
#include <QFileInfo>
#include <QDebug>

ProjectFileController::ProjectFileController(QFileDialogAdapter *fileDialog,
                                             QFileAdapter *file,
                                             ProjectFileReader *reader,
                                             ProjectFileWriter *writer,
                                             FileStateTracker *stateTracker,
                                             AppSettings *settings,
                                             QMessageBoxProvider *messageBox) : QObject()
{
    model = nullptr;
    sourceDirectories = nullptr;
    testDirectories = nullptr;

    this->dialogProvider = fileDialog;
    this->projectFile = file;
    this->reader = reader;
    this->writer = writer;
    this->stateTracker = stateTracker;
    this->settings = settings;
    this->messageBox = messageBox;

    filterString = tr("Requirment Files (*.req)");
}

ProjectFileController::~ProjectFileController()
{
    delete dialogProvider;
    delete projectFile;
    delete reader;
    delete writer;
    delete messageBox;
}

void ProjectFileController::setModel(RequirementsModel *model)
{
    this->model = model;
}

RequirementsModel *ProjectFileController::getRequirementsModel()
{
    return model;
}

void ProjectFileController::injectDirectoryModels(DirectoryListModel *sourceDirectories,
                                                  DirectoryListModel *testDirectories)
{
    this->sourceDirectories = sourceDirectories;
    this->testDirectories = testDirectories;
}

DirectoryListModel *ProjectFileController::sourceDirModel() const
{
    return sourceDirectories;
}

DirectoryListModel *ProjectFileController::testDirModel() const
{
    return testDirectories;
}

void ProjectFileController::setProgrammingLanguage(const QString &value)
{
    programmingLanguage = value;
    emit programmingLanguageChanged(value);
}

QString ProjectFileController::getProgrammingLanguage() const
{
    return programmingLanguage;
}

void ProjectFileController::save()
{
    QString currentPath = stateTracker->filePath();

    if(currentPath.isEmpty())
        saveAs();
    else{
        projectFile->setFileName(currentPath);
        writer->save(this, projectFile);
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
        stateTracker->setFilePath(filePath);
        writer->save(this, projectFile);
        stateTracker->setChanged(false);
        saveAsStartDirectory(filePath);
    }
}

void ProjectFileController::load()
{
    askSaveUnsavedChanges();

    QString startDir = settings->directory();

    QString filePath = dialogProvider->getOpenFileName(0, tr("Open file"),
                                                       startDir, filterString);

    if(!filePath.isEmpty()){
        try{
            sourceDirModel()->clear();
            testDirModel()->clear();
            model->clearModel();
            projectFile->setFileName(filePath);

            // stateTracker->setFilePath() must be called
            // before parsing the project file, because
            // the FileStateTracker is used to find the
            // directory with stored images.
            stateTracker->setFilePath(filePath);
            reader->load(this, projectFile);
            stateTracker->setChanged(false);
            saveAsStartDirectory(filePath);
            emit fileLoaded();
        }
        catch(...){
            QMessageBox::information(0, tr("Error"), tr("The file could not be loaded."));
        }
    }
}

void ProjectFileController::newFile()
{
    askSaveUnsavedChanges();
    model->clearModel();
    projectFile->setFileName(QString());
    stateTracker->setFilePath(QString());
    stateTracker->setChanged(false);
    sourceDirModel()->clear();
    testDirModel()->clear();
    emit fileLoaded();
}

void ProjectFileController::askSaveUnsavedChanges()
{
    if(stateTracker->unsavedChanges()){
        QString title = tr("Unsaved changes");
        QString question = tr("Save changes?");
        QMessageBox::StandardButton result = messageBox->showQuestion(0, title, question);
        if(result == QMessageBox::Yes){
            save();
        }
    }
}

void ProjectFileController::saveAsStartDirectory(const QString &fPath)
{
    QFileInfo fInfo(fPath);
    QString directoryPath = fInfo.absolutePath();

    settings->setDirectory(directoryPath);
}
