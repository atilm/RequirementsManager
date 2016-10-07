#ifndef FREEFORMREPORTGENERATOR_H
#define FREEFORMREPORTGENERATOR_H

#include <memory>

#include <QStringList>

#include "htmlgenerator.h"
#include "reportgenerator.h"
#include "requirementsmodeliterator.h"
#include "textdocumentserializer.h"
using namespace std;

class FreeFormReportGenerator : public ReportGenerator
{
public:
    FreeFormReportGenerator(shared_ptr<HtmlTemplateFactory> templateFactory,
                            shared_ptr<TextDocumentSerializer> documentSerializer,
                            shared_ptr<HtmlGenerator> htmlGenerator);
    virtual ~FreeFormReportGenerator();

    virtual QString getTypeString();
    virtual QString getDescription();
    virtual void setModel(shared_ptr<RequirementsModel> model);
    virtual void generate(const QString &filePath);

private:
    QFile file;
    QTextStream out;
    shared_ptr<HtmlTemplateFactory> templateFactory;
    shared_ptr<TextDocumentSerializer> documentSerializer;
    shared_ptr<HtmlGenerator> htmlGenerator;
    shared_ptr<RequirementsModel> model;
    shared_ptr<RequirementsModelIterator> modelIterator;

    Requirement::Type currentType;
    QStringList contentLines;
    HtmlTemplate *documentTemplate;

    void initializeTemplates();
    QString generateHtml();
    QString generateContent();
    void buildCustomPart();
    void buildDesignSpecification();
    void buildLinesForCurrentItem();
    void buildCurrentDesignSpecItem();
    bool isUserOrFunctionalRequirement(Requirement *requirement);
    bool isUserOrFunctionalRequirement(Requirement::Type type);
    void openOrCloseTables(Requirement *requirement);
    bool typeChanged(Requirement::Type current, Requirement::Type next);
    void closeCurrentTable(Requirement::Type type);
    void closeTableAtEnd();
    void openNextTable(Requirement::Type type);
    QString buildSectionString(Requirement *requirement);
    QString buildTableString(Requirement *requirement);
    QString buildRequirementString(Requirement *requirement,
                                   bool showDescription = true);
};

#endif // FREEFORMREPORTGENERATOR_H
