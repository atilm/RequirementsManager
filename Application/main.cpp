#include "mainwindow.h"
#include <QApplication>
#include "cppreader.h"
#include "preventiveactionfactory.h"
#include "riskscenariotextedit.h"
#include "testnamelineedit.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppSettings *appSettings = new AppSettings();
    appSettings->load();

    shared_ptr<FileStateTracker> fileState(make_shared<FileStateTracker>());
    RichTextResourceManager *docResourcesManager = new RichTextResourceManager(fileState);

    AttributeContext *attributeContext = new AttributeContext(fileState);
    AttributeContainerFactory *attributes = new AttributeContainerFactory(attributeContext);

    UniqueIDManager *idManager = new UniqueIDManager();

    LinkContext *linkContext = new LinkContext(fileState);
    LinkContainerFactory *links = new LinkContainerFactory(linkContext, idManager);

    RichTextController *richText = new RichTextController();

    QMenu *requirementsContextMenu = new QMenu();
    RequirementsView *requirementsView = new RequirementsView(new QMessageBoxProvider(),
                                                              requirementsContextMenu);
    DescriptionView *descriptionView = new DescriptionView(docResourcesManager,
                                                           fileState,
                                                           new ResizeImageDialog());

    QFileDialogAdapter *fileDialog = new QFileDialogAdapter();
    QFileAdapter *file = new QFileAdapter();
    ProjectFileReader *reader = new ProjectFileReader(new QXmlStreamReader(),
                                                      docResourcesManager);

    TextDocumentSerializer *serializer = new TextDocumentSerializer(docResourcesManager);
    ProjectFileWriter *writer = new ProjectFileWriter(new QXmlStreamWriter(),
                                                      serializer,
                                                      docResourcesManager);

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

    RiskAssessmentDialog *raDialog = new RiskAssessmentDialog(new RiskScenarioTextEdit(),
                                                              new QPlainTextEditAdapter(),
                                                              new RiskAssessmentTable(),
                                                              new RiskAssessmentTable());

    PreventiveActionDialog *paDialog = new PreventiveActionDialog();
    paDialog->injectWidgets(new TestNameLineEdit(),
                            new TestNameLineEdit(),
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
                                            new QTextStreamAdapter(),
                                            make_shared<DirectoryLister>(make_shared<QDir>())));

    SettingsDialog *settingsDialog = new SettingsDialog(readerProvider,
                                                        fileController,
                                                        appSettings,
                                                        0);

    SourceCodeController *sourceController = new SourceCodeController(new QFileSystemWatcher(),
                                                                      fileState,
                                                                      fileController,
                                                                      readerProvider,
                                                                      new HtmlGenerator(),
                                                                      0);
    RequirementFactory *factory = new RequirementFactory(fileState, idManager,
                                                         attributes, links,
                                                         sourceController, appSettings);
    PreventiveActionFactory *actionFactory = new PreventiveActionFactory(fileState,
                                                                         sourceController);

    reader->injectRequirementFactory(factory);
    reader->injectPreventiveActionFacotry(actionFactory);

    RequirementToModelMapper *dataMapper = new RequirementToModelMapper(attributeContext);
    shared_ptr<RequirementsModel> requirements(new RequirementsModel(factory,
                                                                     fileState,
                                                                     attributeContext,
                                                                     linkContext,
                                                                     dataMapper));
    requirements->init();

    ReportController *reportController = new ReportController(new ReportGeneratorFactory(fileState),
                                                              fileState);

    AppSettingsDialog *appSettingsDialog = new AppSettingsDialog(appSettings);

    MainWindow w(fileController, requirements, richText,
                 fileState, msg, appSettings, attributeEditor, raEditController,
                 linkTypeEditor, linkController,
                 sourceController,
                 appSettingsDialog,
                 settingsDialog,
                 reportController, 0);

    w.injectViews(requirementsView, descriptionView);
    w.injectRiskViews(riskDescriptionView, riskTableView, actionTableView);
    w.show();

    return a.exec();
}
