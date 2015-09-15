#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UniqueIDManager *idManager = new UniqueIDManager();
    RequirementFactory *factory = new RequirementFactory(idManager);
    RequirementsModel *requirements = new RequirementsModel(factory);

    RichTextController *richText = new RichTextController();

    RequirementsView *requirementsView = new RequirementsView();
    DescriptionView *descriptionView = new DescriptionView();

    MainWindow w(requirements, richText);
    w.injectViews(requirementsView, descriptionView);
    w.show();

    return a.exec();
}
