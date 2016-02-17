#ifndef SOURCECODECONTROLLER_H
#define SOURCECODECONTROLLER_H

#include <QListView>
#include <QObject>

#include "sourcecodemodel.h"
#include "sourcecodereaderprovider.h"
#include "projectfilecontroller.h"

class SourceCodeController : public QObject
{
    Q_OBJECT
public:
    explicit SourceCodeController(ProjectFileController *project,
                                  SourceCodeReaderProvider *readerProvider,
                                  QObject *parent = 0);
    virtual ~SourceCodeController();

    virtual void injectViews(QListView *moduleView,
                             QListView *functionView,
                             QListView *testView);

signals:

public slots:
    virtual void parseProjectCode();

private:
    QListView *moduleView;
    QListView *functionView;
    QListView *testView;
    SourceCodeModel *model;
    SourceCodeReaderProvider *readerProvider;
    ProjectFileController *project;

private slots:
    void handleClassSelectionChanged(const QModelIndex &current,
                                     const QModelIndex &previous);
};

#endif // SOURCECODECONTROLLER_H
