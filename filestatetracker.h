#ifndef FILESTATETRACKER_H
#define FILESTATETRACKER_H

#include <QObject>
#include <QString>

/*! Store the state of the project file.

  Stores the path of the opened file and its
  "changed" state.

  An object of this class must be passed to all
  objects that might perform changes on the data
  that will be saved to the project file.

  When such an object performs any changes it must
  announce this by calling setChanged(true).
 */
class FileStateTracker : public QObject
{
    Q_OBJECT
public:
    FileStateTracker();
    virtual ~FileStateTracker();

    /*!
     Returns the project file path.
     */
    virtual QString filePath() const;

    /*!
     Sets the project file path.
     */
    virtual void setFilePath(const QString &path);

    /*!
     Returns the current "changed" state.
     */
    virtual bool unsavedChanges() const;

    /*!
     Sets the current "changed" state.
     */
    virtual void setChanged(bool state);

signals:
    void filePathChanged(const QString &path);
    void changedStateChanged(bool state);

private:
    QString _filePath;
    bool _changed;
};

#endif // FILESTATETRACKER_H
