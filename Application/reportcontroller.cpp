#include "reportcontroller.h"
#include <QDesktopServices>
#include <QFileInfo>
#include <QMessageBox>

ReportController::ReportController(ReportGeneratorProvider *generatorProvider,
                                   shared_ptr<FileStateTracker> fileState,
                                   ReportTypeChooserDialog *typeChooser,
                                   QObject *parent)
    : QObject(parent)
{
    this->generatorProvider = generatorProvider;
    this->fileState = fileState;
    this->typeChooser = typeChooser;

    this->typeChooser->setGeneratorProvider(generatorProvider);
}

ReportController::~ReportController()
{
    delete generatorProvider;
}

void ReportController::setModel(shared_ptr<RequirementsModel> model)
{
    this->model = model;
}

void ReportController::generateReport()
{
    if(!model)
        throw runtime_error("ReportController: model has not been set.");

    if(!typeChooser->exec()){
        return;
    }

    if(!fileState->filePath().isEmpty()){
        QString targetFile = swapFileExtension(fileState->filePath(), ".html");

        ReportGenerator *generator =
                generatorProvider->getGenerator(typeChooser->getType());
        generator->setModel(model);
        generator->generate(targetFile);

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

