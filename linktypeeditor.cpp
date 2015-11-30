#include "linktypeeditor.h"
#include "ui_linkeditor.h"

LinkTypeEditor::LinkTypeEditor(LinkContext *context, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinkEditor)
{
    ui->setupUi(this);
    setWindowTitle(tr("Edit link types"));

    this->context = context;

    ui->linkTypeView->setModel(context);

    connect(ui->addLinkTypeButton, SIGNAL(clicked()),
            this, SLOT(handleAddClicked()));
    connect(ui->removeLinkTypeButton, SIGNAL(clicked()),
            this, SLOT(handleRemoveClicked()));
    connect(ui->renameLinkTypeButton, SIGNAL(clicked()),
            this, SLOT(handleRenameClicked()));
}

LinkTypeEditor::~LinkTypeEditor()
{
    delete ui;
    delete context;
}

void LinkTypeEditor::handleAddClicked()
{
    context->addLinkType(takeName());
}

void LinkTypeEditor::handleRemoveClicked()
{
    context->removeLinkType(ui->linkTypeView->selectionModel()->currentIndex());
}

void LinkTypeEditor::handleRenameClicked()
{
    context->renameLinkType(ui->linkTypeView->selectionModel()->currentIndex(),
                            takeName());
}

QString LinkTypeEditor::takeName()
{
    QString name = ui->linkTypeEdit->text();
    ui->linkTypeEdit->clear();
    return name;
}
