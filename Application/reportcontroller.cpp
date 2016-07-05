#include "reportcontroller.h"
#include <QDesktopServices>
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

void ReportController::setModel(shared_ptr<RequirementsModel> model)
{
    this->model = model;
}

void ReportController::generateReport()
{
    if(!model)
        throw runtime_error("ReportController: model has not been set.");

    if(!fileState->filePath().isEmpty()){
        QString targetFile = swapFileExtension(fileState->filePath(), ".html");

        ReportGenerator *generator = generatorFactory->newGenerator("html");
        generator->setModel(model);
        generator->generate(targetFile);
        delete generator;

        QDesktopServices::openUrl(QString("file:///%1")
                                  .arg(targetFile));
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

