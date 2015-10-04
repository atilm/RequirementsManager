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
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Data Type"));

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(handleAddClicked()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(handleRemoveClicked()));
}

AttributeEditor::~AttributeEditor()
{
    delete ui;
}

void AttributeEditor::updateView()
{
    ui->nameEdit->clear();

    for(int i=0;i<ui->tableWidget->rowCount();i++)
        ui->tableWidget->removeRow(0);

    QList<QString> names = context->names();
    foreach(QString name, names){
        QTableWidgetItem *nameItem = new QTableWidgetItem(name);
        QTableWidgetItem *typeItem = new QTableWidgetItem(context->typeString(name));

        int newRowIndex = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(newRowIndex);
        ui->tableWidget->setItem(newRowIndex, 0, nameItem);
        ui->tableWidget->setItem(newRowIndex, 1, typeItem);
    }
}

void AttributeEditor::exec()
{
    updateView();
    QDialog::exec();
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
    AttributeContext::DataType type = static_cast<AttributeContext::DataType>(ui->typeBox->itemData(ui->typeBox->currentIndex()).toInt());
    context->addAttribute(name, type);

    updateView();
}

void AttributeEditor::handleRemoveClicked()
{
    int row = ui->tableWidget->currentRow();
    QString name = ui->tableWidget->item(row, 0)->text();
    context->removeAttribute(name);

    updateView();
}
