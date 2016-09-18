#ifndef PROJECTFILECONTROLLER_H
#define PROJECTFILECONTROLLER_H

#include "qfileadapter.h"
#include "qfiledialogadapter.h"
#include "requirementsmodel.h"
#include "projectfilereader.h"
#include "projectfilewriter.h"
#include "filestatetracker.h"
#include "appsettings.h"
#include "qmessageboxprovider.h"
#include "directorylistmodel.h"
#include "directorylistmodel.h"
#include "requirementrefcounter.h"
#include "uniqueidmanager.h"

#include <memory>
using namespace std;

//! Encapsulates all read/write operations to load and save the project
/*!
  The class takes a pointer to a RequirementsModel.
  Calling the load slot will result in an attempt to read project data from
  file and write it into the RequirementsModel. Calling the save slot
  will result in saving the RequirementsModel to file. File open and save
  dialogs will be shown as needed.
 */
class ProjectFileController : public QObject
{
    Q_OBJECT
public:
    ProjectFileController(QFileDialogAdapter *fileDialog, QFileAdapter *file,
                          ProjectFileReader *reader, ProjectFileWriter *writer,
                          shared_ptr<FileStateTracker> stateTracker, AppSettings *settings,
                          QMessageBoxProvider *messageBox);
    virtual ~ProjectFileController();

    virtual void setModel(shared_ptr<RequirementsModel> model);
    virtual shared_ptr<RequirementsModel> getRequirementsModel();
    virtual void injectDirectoryModels(DirectoryListModel *sourceDirectories,
                                       DirectoryListModel *testDirectories);

    virtual DirectoryListModel* sourceDirModel() const;
    virtual DirectoryListModel* testDirModel() const;

    virtual void setProgrammingLanguage(const QString &value);
    virtual QString getProgrammingLanguage() const;

signals:
    void beginLoadFile();
    void fileLoaded();
    void programmingLanguageChanged(const QString &name);

public slots:
    virtual void save();
    virtual void saveAs();
    virtual void load();
    virtual void newFile();

    void askSaveUnsavedChanges();

private:
    shared_ptr<RequirementsModel> model;
    QString programmingLanguage;
    DirectoryListModel *sourceDirectories;
    DirectoryListModel *testDirectories;
    QFileDialogAdapter *dialogProvider;
    QFileAdapter *projectFile;
    ProjectFileReader *reader;
    ProjectFileWriter *writer;
    shared_ptr<FileStateTracker> stateTracker;
    AppSettings *settings;
    QMessageBoxProvider *messageBox;

    QString filterString;

    void saveAsStartDirectory(const QString &fPath);
};

#endif // PROJECTFILECONTROLLER_H
