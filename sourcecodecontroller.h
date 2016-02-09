#ifndef SOURCECODECONTROLLER_H
#define SOURCECODECONTROLLER_H

#include <QListView>
#include <QObject>

#include "sourcecodemodel.h"

class SourceCodeController : public QObject
{
    Q_OBJECT
public:
    explicit SourceCodeController(QObject *parent = 0);
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
};

#endif // SOURCECODECONTROLLER_H
