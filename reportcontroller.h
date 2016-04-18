#ifndef REPORTCONTROLLER_H
#define REPORTCONTROLLER_H

#include <QObject>
#include "filestatetracker.h"
#include "reportgeneratorfactory.h"

class ReportController : public QObject
{
    Q_OBJECT
public:
    ReportController(ReportGeneratorFactory *generatorFactory,
                     FileStateTracker *fileState,
                     QObject *parent = 0);
    virtual ~ReportController();

public slots:
    virtual void generateReport();

private:
    FileStateTracker *fileState;
    ReportGeneratorFactory *generatorFactory;

    QString swapFileExtension(const QString &filePath, const QString &newExtension);
};

#endif // REPORTCONTROLLER_H
