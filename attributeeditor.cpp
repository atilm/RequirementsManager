#include "attributeeditor.h"
#include "ui_attributeeditor.h"

AttributeEditor::AttributeEditor(AttributeContext *context, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttributeEditor)
{
    ui->setupUi(this);
    this->context = context;
}

AttributeEditor::~AttributeEditor()
{
    delete ui;
}

void AttributeEditor::updateView()
{
    ui->tableWidget->clear();

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

void AttributeEditor::handleAddClicked()
{

}

void AttributeEditor::handleRemoveClicked()
{

}
