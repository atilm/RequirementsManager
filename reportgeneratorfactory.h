#ifndef REPORTGENERATORFACTORY_H
#define REPORTGENERATORFACTORY_H

#include "reportgenerator.h"

class ReportGeneratorFactory
{
public:
    ReportGeneratorFactory(FileStateTracker *fileState);
    virtual ~ReportGeneratorFactory();

    virtual ReportGenerator *newGenerator(const QString &type);

private:
    FileStateTracker *fileState;
    ReportGenerator *newHtmlReportGenerator();
};

#endif // REPORTGENERATORFACTORY_H
