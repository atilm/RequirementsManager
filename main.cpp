#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppSettings *appSettings = new AppSettings();
    FileStateTracker *fileState = new FileStateTracker();

    AttributeContext *attributeContext = new AttributeContext();
    AttributeContainerFactory *attributes = new AttributeContainerFactory(attributeContext);

    UniqueIDManager *idManager = new UniqueIDManager();
    RequirementFactory *factory = new RequirementFactory(idManager, attributes);
    RequirementToModelMapper *dataMapper = new RequirementToModelMapper(attributeContext);
    RequirementsModel *requirements = new RequirementsModel(factory, fileState,
                                                            attributeContext, dataMapper);
    requirements->init();

    RichTextController *richText = new RichTextController();

    RequirementsView *requirementsView = new RequirementsView();
    DescriptionView *descriptionView = new DescriptionView();

    QFileDialogAdapter *fileDialog = new QFileDialogAdapter();
    QFileAdapter *file = new QFileAdapter();
    ProjectFileReader *reader = new ProjectFileReader(new QXmlStreamReader());
    ProjectFileWriter *writer = new ProjectFileWriter(new QXmlStreamWriter());

    QMessageBoxProvider *fileControllerMsg = new QMessageBoxProvider();

    ProjectFileController *fileController =
            new ProjectFileController(fileDialog, file,
                                      reader, writer,
                                      fileState, appSettings,
                                      fileControllerMsg);

    QMessageBoxProvider *msg = new QMessageBoxProvider();

    AttributeEditor *attributeEditor = new AttributeEditor(attributeContext);

    MainWindow w(fileController, requirements, richText, fileState, msg, appSettings, attributeEditor);
    w.injectViews(requirementsView, descriptionView);
    w.show();

    return a.exec();
}
