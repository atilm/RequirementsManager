#ifndef HTMLREPORTGENERATOR_H
#define HTMLREPORTGENERATOR_H

#include "reportgenerator.h"
#include "requirementsmodel.h"

class HtmlReportGenerator : public ReportGenerator
{
public:
    HtmlReportGenerator();
    virtual ~HtmlReportGenerator();

    virtual void setModel(RequirementsModel *model);
    virtual void generate(const QString &filePath);

private:
    RequirementsModel *model;
};

#endif // HTMLREPORTGENERATOR_H
