#ifndef REPORTCONTROLLER_H
#define REPORTCONTROLLER_H

#include <QObject>
#include "filestatetracker.h"
#include "reportgeneratorfactory.h"
#include "requirementsmodel.h"

#include <memory>
using namespace std;

class ReportController : public QObject
{
    Q_OBJECT
public:
    ReportController(ReportGeneratorFactory *generatorFactory,
                     shared_ptr<FileStateTracker> fileState,
                     QObject *parent = 0);
    virtual ~ReportController();

    virtual void setModel(shared_ptr<RequirementsModel> model);

public slots:
    virtual void generateReport();

private:
    shared_ptr<FileStateTracker> fileState;
    ReportGeneratorFactory *generatorFactory;
    shared_ptr<RequirementsModel> model;

    QString swapFileExtension(const QString &filePath, const QString &newExtension);
};

#endif // REPORTCONTROLLER_H
