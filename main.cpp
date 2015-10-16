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

    QMenu *requirementsContextMenu = new QMenu();
    RequirementsView *requirementsView = new RequirementsView(requirementsContextMenu);
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

    RiskDescriptionView *riskDescriptionView = new RiskDescriptionView();
    RiskTableView *riskTableView = new RiskTableView();
    PreventiveActionTableView *actionTableView = new PreventiveActionTableView();


    RiskAssessmentDialog *riskDialog = new RiskAssessmentDialog(new QPlainTextEditAdapter(),
                                                                new RiskAssessmentTable(),
                                                                new RiskAssessmentTable());

    MainWindow w(fileController, requirements, richText,
                 fileState, msg, appSettings, attributeEditor,
                 riskDialog);
    w.injectViews(requirementsView, descriptionView);
    w.injectRiskViews(riskDescriptionView, riskTableView, actionTableView);
    w.show();

    return a.exec();
}
