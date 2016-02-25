#ifndef SOURCECODECONTROLLER_H
#define SOURCECODECONTROLLER_H

#include <QListView>
#include <QObject>
#include <QTextDocument>

#include "sourcecodemodel.h"
#include "sourcecodereaderprovider.h"
#include "projectfilecontroller.h"
#include "descriptionview.h"
#include "riskdescriptionview.h"
#include "requirementfactory.h"
#include "requirementsview.h"
#include "preventiveactiontableview.h"
#include "testnode.h"


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
    virtual void injectDescriptionView(DescriptionView *view);
    virtual void injectRiskDescriptionView(RiskDescriptionView *view);
    virtual void injectRequirementsFactory(RequirementFactory *reqFactory);
    virtual void injectRequirementsView(RequirementsView *reqView);
    virtual void injectPreventiveActionView(PreventiveActionTableView *actionView);

    virtual QString getDescription(SourceAddress address);
    virtual TestNode *getTestNode(SourceAddress address);

signals:

public slots:
    virtual void parseProjectCode();

private:
    QListView *moduleView;
    QListView *functionView;
    QListView *testView;
    DescriptionView *functionSpecView;
    RiskDescriptionView *testSpecView;
    QTextDocument document;
    SourceCodeModel *model;
    SourceCodeReaderProvider *readerProvider;
    ProjectFileController *project;
    RequirementFactory *reqFactory;
    RequirementsView *reqView;
    PreventiveActionTableView *preventiveActionView;

private slots:
    void handleClassSelectionChanged(const QModelIndex &current,
                                     const QModelIndex &previous);
    void handleFunctionSelectionChanged(const QModelIndex &current,
                                        const QModelIndex &previous);
    void handleTestSelectionChanged(const QModelIndex &current,
                                    const QModelIndex &previous);
    void handleClassOrFunctionDoubleClicked(const QModelIndex &index);
    void handleTestDoubleClicked(const QModelIndex &index);

private:
    void showDescription(const QModelIndex &index);
    void showTestDescription(const QModelIndex &index);
};

#endif // SOURCECODECONTROLLER_H
