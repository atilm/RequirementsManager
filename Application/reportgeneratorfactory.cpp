#include "reportgeneratorfactory.h"
#include "htmlreportgenerator.h"

ReportGeneratorProvider::ReportGeneratorProvider()
{
}

ReportGeneratorProvider::~ReportGeneratorProvider()
{

}

void ReportGeneratorProvider::addGenerator(ReportGenerator *generator)
{
    generators[generator->getTypeString()] = generator;
}

QStringList ReportGeneratorProvider::availableGenerators()
{
    QStringList types;

    foreach(QString type, generators.keys())
        types.append(type);

    return types;
}

ReportGenerator *ReportGeneratorProvider::getGenerator(const QString &type) const
{
    if(!generators.contains(type)){
        throw std::runtime_error(
                    QString("No generator of type %1").arg(type).toStdString());
    }

    return generators[type];
}

QString ReportGeneratorProvider::getDescription(const QString &type) const
{
    if(generators.contains(type)){
        return generators[type]->getDescription();
    }
    else{
        return QString();
    }
}

