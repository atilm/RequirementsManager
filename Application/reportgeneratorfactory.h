#ifndef REPORTGENERATORFACTORY_H
#define REPORTGENERATORFACTORY_H

#include "reportgenerator.h"

class ReportGeneratorFactory
{
public:
    ReportGeneratorFactory(shared_ptr<FileStateTracker> fileState);
    virtual ~ReportGeneratorFactory();

    virtual ReportGenerator *newGenerator(const QString &type);

private:
    shared_ptr<FileStateTracker> fileState;
    ReportGenerator *newHtmlReportGenerator();
};

#endif // REPORTGENERATORFACTORY_H
