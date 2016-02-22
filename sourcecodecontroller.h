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

private slots:
    void handleClassSelectionChanged(const QModelIndex &current,
                                     const QModelIndex &previous);
    void handleFunctionSelectionChanged(const QModelIndex &current,
                                        const QModelIndex &previous);
    void showDescription(const QModelIndex &index);
};

#endif // SOURCECODECONTROLLER_H
