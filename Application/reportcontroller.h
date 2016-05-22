#ifndef REPORTCONTROLLER_H
#define REPORTCONTROLLER_H

#include <QObject>
#include "filestatetracker.h"
#include "reportgeneratorfactory.h"
#include "requirementsmodel.h"

class ReportController : public QObject
{
    Q_OBJECT
public:
    ReportController(ReportGeneratorFactory *generatorFactory,
                     FileStateTracker *fileState,
                     QObject *parent = 0);
    virtual ~ReportController();

    virtual void setModel(RequirementsModel *model);

public slots:
    virtual void generateReport();

private:
    FileStateTracker *fileState;
    ReportGeneratorFactory *generatorFactory;
    RequirementsModel *model;

    QString swapFileExtension(const QString &filePath, const QString &newExtension);
};

#endif // REPORTCONTROLLER_H
