#include "mainwindow.h"
#include <QApplication>
#include "cppreader.h"
#include "preventiveactionfactory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppSettings *appSettings = new AppSettings();
    FileStateTracker *fileState = new FileStateTracker();

    AttributeContext *attributeContext = new AttributeContext();
    AttributeContainerFactory *attributes = new AttributeContainerFactory(attributeContext);

    UniqueIDManager *idManager = new UniqueIDManager();

    LinkContext *linkContext = new LinkContext();
    LinkContainerFactory *links = new LinkContainerFactory(linkContext, idManager);

    RichTextController *richText = new RichTextController();

    QMenu *requirementsContextMenu = new QMenu();
    RequirementsView *requirementsView = new RequirementsView(requirementsContextMenu);
    DescriptionView *descriptionView = new DescriptionView();

    QFileDialogAdapter *fileDialog = new QFileDialogAdapter();
    QFileAdapter *file = new QFileAdapter();
    ProjectFileReader *reader = new ProjectFileReader(new QXmlStreamReader());
    ProjectFileWriter *writer = new ProjectFileWriter(new QXmlStreamWriter(),
                                                      new TextDocumentSerializer());

    QMessageBoxProvider *fileControllerMsg = new QMessageBoxProvider();

    ProjectFileController *fileController =
            new ProjectFileController(fileDialog, file,
                                      reader, writer,
                                      fileState, appSettings,
                                      fileControllerMsg);

    fileController->injectDirectoryModels(new DirectoryListModel(fileState),
                                          new DirectoryListModel(fileState));

    QMessageBoxProvider *msg = new QMessageBoxProvider();

    AttributeEditor *attributeEditor = new AttributeEditor(attributeContext);

    HtmlGenerator *displayHtml = new HtmlGenerator(new HtmlTemplateFactory());
    RiskDescriptionView *riskDescriptionView = new RiskDescriptionView(displayHtml);

    RiskAssessmentDialog *raDialog = new RiskAssessmentDialog(new QPlainTextEditAdapter(),
                                                              new QPlainTextEditAdapter(),
                                                              new RiskAssessmentTable(),
                                                              new RiskAssessmentTable());

    PreventiveActionDialog *paDialog = new PreventiveActionDialog();
    paDialog->injectWidgets(new QLineEditAdapter(),
                            new QLineEditAdapter(),
                            new QLineEditAdapter(),
                            new QPlainTextEditAdapter(),
                            new QPlainTextEditAdapter(),
                            new QPlainTextEditAdapter());

    RiskAssessmentEditController *raEditController = new RiskAssessmentEditController(raDialog,
                                                                                      paDialog);
    RiskTableView *riskTableView = new RiskTableView();
    PreventiveActionTableView *actionTableView = new PreventiveActionTableView();

    LinkTypeEditor *linkTypeEditor = new LinkTypeEditor(linkContext);

    LinkController *linkController = new LinkController();
    linkController->setRequirementsView(requirementsView);

    SourceCodeReaderProvider *readerProvider = new SourceCodeReaderProvider();
    readerProvider->addReader(new CppReader(new QFileAdapter(),
                                            new QTextStreamAdapter()));

    SettingsDialog *settingsDialog = new SettingsDialog(readerProvider,
                                                        fileController,
                                                        appSettings,
                                                        0);

    SourceCodeController *sourceController = new SourceCodeController(fileState,
                                                                      fileController,
                                                                      readerProvider,
                                                                      0);
    RequirementFactory *factory = new RequirementFactory(fileState, idManager,
                                                         attributes, links,
                                                         sourceController);
    PreventiveActionFactory *actionFactory = new PreventiveActionFactory(fileState,
                                                                         sourceController);

    reader->injectRequirementFactory(factory);
    reader->injectPreventiveActionFacotry(actionFactory);

    RequirementToModelMapper *dataMapper = new RequirementToModelMapper(attributeContext);
    RequirementsModel *requirements = new RequirementsModel(factory, fileState,
                                                            attributeContext, linkContext,
                                                            dataMapper);
    requirements->init();

    MainWindow w(fileController, requirements, richText,
                 fileState, msg, appSettings, attributeEditor, raEditController,
                 linkTypeEditor, linkController,
                 sourceController, settingsDialog, 0);
    w.injectViews(requirementsView, descriptionView);
    w.injectRiskViews(riskDescriptionView, riskTableView, actionTableView);
    w.show();

    return a.exec();
}
