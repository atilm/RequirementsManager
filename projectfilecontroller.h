#ifndef PROJECTFILECONTROLLER_H
#define PROJECTFILECONTROLLER_H

#include "qfileadapter.h"
#include "qfiledialogadapter.h"
#include "requirementsmodel.h"
#include "projectfilereader.h"
#include "projectfilewriter.h"
#include "filestatetracker.h"
#include "appsettings.h"

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
                          FileStateTracker *stateTracker, AppSettings *settings);
    virtual ~ProjectFileController();

    virtual void setModel(RequirementsModel *model);

public slots:
    virtual void save();
    virtual void saveAs();
    virtual void load();

private:
    RequirementsModel *model;
    QFileDialogAdapter *dialogProvider;
    QFileAdapter *projectFile;
    ProjectFileReader *reader;
    ProjectFileWriter *writer;
    FileStateTracker *stateTracker;
    AppSettings *settings;

    QString filterString;
};

#endif // PROJECTFILECONTROLLER_H
