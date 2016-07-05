#ifndef SOURCECODECONTROLLER_H
#define SOURCECODECONTROLLER_H

#include <QFileSystemWatcher>
#include <QListView>
#include <QObject>
#include <QTextDocument>

#include "htmlgenerator.h"
#include "sourcecodemodel.h"
#include "sourcecodereaderprovider.h"
#include "projectfilecontroller.h"
#include "descriptionview.h"
#include "riskdescriptionview.h"
#include "requirementfactory.h"
#include "requirementsview.h"
#include "preventiveactiontableview.h"
#include "testnode.h"
#include "filestatetracker.h"


class SourceCodeController : public QObject
{
    Q_OBJECT
public:
    explicit SourceCodeController(QFileSystemWatcher *fileWatcher,
                                  shared_ptr<FileStateTracker> stateTracker,
                                  ProjectFileController *project,
                                  SourceCodeReaderProvider *readerProvider,
                                  HtmlGenerator *htmlGenerator,
                                  QObject *parent = 0);
    virtual ~SourceCodeController();

    virtual void injectViews(QListView *moduleView,
                             QListView *functionView,
                             QListView *testView);
    virtual void injectDescriptionView(DescriptionView *view);
    virtual void injectRiskDescriptionView(RiskDescriptionView *view);
    virtual void injectRequirementsFactory(RequirementFactory *reqFactory);
    virtual void injectRequirementsView(RequirementsView *reqView);
    virtual void injectPreventiveActionView(PreventiveActionTableView *actionView);

    virtual QTextDocument* getDescription(SourceAddress address);
    virtual TestNode *getTestNode(SourceAddress address);

signals:

public slots:
    virtual void parseProjectCode();

private:
    QFileSystemWatcher *fileWatcher;
    bool handlingFile;
    shared_ptr<FileStateTracker> stateTracker;
    QListView *moduleView;
    QListView *functionView;
    QListView *testView;
    DescriptionView *functionSpecView;
    RiskDescriptionView *testSpecView;
    SourceCodeModel *model;
    SourceCodeReaderProvider *readerProvider;
    ProjectFileController *project;
    RequirementFactory *reqFactory;
    RequirementsView *reqView;
    PreventiveActionTableView *preventiveActionView;
    HtmlGenerator *htmlGenerator;
    QTextDocument description;

private slots:
    void handleClassSelectionChanged(const QModelIndex &current,
                                     const QModelIndex &previous);
    void handleFunctionSelectionChanged(const QModelIndex &current,
                                        const QModelIndex &previous);
    void handleTestSelectionChanged(const QModelIndex &current,
                                    const QModelIndex &previous);
    void handleClassClicked(const QModelIndex &index);
    void handleFunctionClicked(const QModelIndex &index);
    void handleTestClicked(const QModelIndex &index);
    void handleClassOrFunctionDoubleClicked(const QModelIndex &index);
    void handleTestDoubleClicked(const QModelIndex &index);
    void handleFileChanged();


private:
    void showDescription(const QModelIndex &index);
    void showTestDescription(const QModelIndex &index);
    void disconnectAllViewSlots();
    void disconnectFunctionView();
    void disconnectTestView();
};

#endif // SOURCECODECONTROLLER_H
