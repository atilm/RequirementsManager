#ifndef FILESTATETRACKER_H
#define FILESTATETRACKER_H

#include <QObject>
#include <QString>
#include <QDir>

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
     Returns the project file name without extension.
     */
    virtual QString fileBaseName() const;

    virtual QDir dir() const;

    /*!
     Sets the project file path.
     */
    virtual void setFilePath(const QString &path);

    /*!
     Converts the path relative to the project file path
     into an absolute path.
     */
    virtual QString toAbsoluteFilePath(const QString relativePath);

    /*!
     Converts an absolute path ionto a path relative to the project
     file path.
     */
    virtual QString toRelativeFilePath(const QString absolutePath);

    /*!
     Returns the current "changed" state.
     */
    virtual bool unsavedChanges() const;

public slots:
    /*!
     Sets the current "changed" state.
     */
    virtual void setChanged(bool state = true);

signals:
    void filePathChanged(const QString &path);
    void changedStateChanged(bool state);

private:
    QString _filePath;
    bool _changed;
};

#endif // FILESTATETRACKER_H
