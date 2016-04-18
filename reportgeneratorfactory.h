#ifndef REPORTGENERATORFACTORY_H
#define REPORTGENERATORFACTORY_H

#include "reportgenerator.h"

class ReportGeneratorFactory
{
public:
    ReportGeneratorFactory();
    virtual ~ReportGeneratorFactory();

    virtual ReportGenerator *newGenerator(const QString &type);

private:
    ReportGenerator *newHtmlReportGenerator();
};

#endif // REPORTGENERATORFACTORY_H
