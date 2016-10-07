#ifndef REPORTGENERATORFACTORY_H
#define REPORTGENERATORFACTORY_H

#include <QStringList>
#include <QMap>

#include "reportgenerator.h"

class ReportGeneratorProvider
{
public:
    ReportGeneratorProvider();
    virtual ~ReportGeneratorProvider();

    virtual void addGenerator(ReportGenerator *generator);
    virtual QStringList availableGenerators();
    virtual ReportGenerator *getGenerator(const QString &type) const;
    virtual QString getDescription(const QString &type) const;

private:
    QMap<QString, ReportGenerator*> generators;
};

#endif // REPORTGENERATORFACTORY_H
