#ifndef SOURCECODECONTROLLER_H
#define SOURCECODECONTROLLER_H

#include <QListView>
#include <QObject>

#include "sourcecodemodel.h"
#include "sourcecodereaderprovider.h"

class SourceCodeController : public QObject
{
    Q_OBJECT
public:
    explicit SourceCodeController(SourceCodeReaderProvider *readerProvider,
                                  QObject *parent = 0);
    virtual ~SourceCodeController();

    virtual void injectViews(QListView *moduleView,
                             QListView *functionView,
                             QListView *testView);

signals:

public slots:

private:
    QListView *moduleView;
    QListView *functionView;
    QListView *testView;
    SourceCodeModel *model;
    SourceCodeReaderProvider *readerProvider;

};

#endif // SOURCECODECONTROLLER_H
