#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RequirementsModel *requirements = new RequirementsModel();
    RichTextController *richText = new RichTextController();

    RequirementsView *requirementsView = new RequirementsView();
    DescriptionView *descriptionView = new DescriptionView();

    MainWindow w(requirements, richText);
    w.injectViews(requirementsView, descriptionView);
    w.show();

    return a.exec();
}
