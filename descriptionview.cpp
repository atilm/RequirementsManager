#include "descriptionview.h"

DescriptionView::DescriptionView(QWidget *parent) :
    QTextEdit(parent)
{
    defaultDocument = new QTextDocument();
    initialize();
}

void DescriptionView::setModel(RequirementsModel *data)
{
    this->data = data;
}

void DescriptionView::switchItem(const QModelIndex &current, const QModelIndex &previous)
{
    try{
        setDocument(data->getDescription(current));

        setEnabled(true);
    }
    catch(...){
        setDocument(defaultDocument);
        setDisabled(true);
    }
}

void DescriptionView::initialize()
{
    setDisabled(true);

    defaultDocument->setPlainText(tr("Click on the \"plus\" buttons to add requirements."));
    setDocument(defaultDocument);
}

