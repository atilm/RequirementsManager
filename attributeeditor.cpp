#include "attributeeditor.h"
#include "ui_attributeeditor.h"

AttributeEditor::AttributeEditor(AttributeContext *context, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttributeEditor)
{
    ui->setupUi(this);
    setWindowTitle(tr("Attribute Editor"));
    this->context = context;

    initTypeBox();

    ui->tableView->setModel(context);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(handleAddClicked()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(handleRemoveClicked()));
}

AttributeEditor::~AttributeEditor()
{
    delete context;
    delete ui;
}


void AttributeEditor::initTypeBox()
{
    ui->typeBox->addItem(context->typeString(AttributeContext::BOOLEAN), AttributeContext::BOOLEAN);
    ui->typeBox->addItem(context->typeString(AttributeContext::INTEGER), AttributeContext::INTEGER);
    ui->typeBox->addItem(context->typeString(AttributeContext::TEXT), AttributeContext::TEXT);
}

void AttributeEditor::handleAddClicked()
{
    QString name = ui->nameEdit->text();
    int typeIndex = ui->typeBox->itemData(ui->typeBox->currentIndex()).toInt();
    AttributeContext::DataType type = static_cast<AttributeContext::DataType>(typeIndex);
    context->addAttribute(name, type);
    ui->nameEdit->clear();
}

void AttributeEditor::handleRemoveClicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    context->removeAttribute(index.row());
}
