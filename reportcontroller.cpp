#include "reportcontroller.h"
#include <QFileInfo>
#include <QMessageBox>

ReportController::ReportController(ReportGeneratorFactory *generatorFactory,
                                   FileStateTracker *fileState,
                                   QObject *parent)
    : QObject(parent)
{
    this->generatorFactory = generatorFactory;
    this->fileState = fileState;
}

ReportController::~ReportController()
{
    delete generatorFactory;
}

void ReportController::generateReport()
{
    if(!fileState->filePath().isEmpty()){
        ReportGenerator *generator = generatorFactory->newGenerator("html");
        generator->generate(swapFileExtension(fileState->filePath(), ".html"));
        delete generator;
    }
    else{
        QMessageBox::information(0,
                                 tr("No project file"),
                                 tr("Save the project before creating a report."));
    }
}

QString ReportController::swapFileExtension(const QString &filePath,
                                            const QString &newExtension)
{
    QFileInfo fInfo(filePath);
    QString extension = fInfo.suffix();

    QString newFilePath = filePath;
    newFilePath.replace(QString(".%1").arg(extension), newExtension);

    return newFilePath;
}

