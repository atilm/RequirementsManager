#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "requirementsmodel.h"
#include <QString>

#include <memory>
using namespace std;

class ReportGenerator
{
public:
    ReportGenerator();
    virtual ~ReportGenerator();

    virtual void setModel(shared_ptr<RequirementsModel> model) = 0;
    virtual void generate(const QString &filePath) = 0;
};

#endif // REPORTGENERATOR_H
