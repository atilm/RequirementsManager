#include "descriptionview.h"

#include <iostream>
using namespace std;

DescriptionView::DescriptionView(QWidget *parent) :
    QTextEdit(parent)
{
    setDisabled(true);
}

void DescriptionView::setModel(RequirementsModel *data)
{
    this->data = data;
}

void DescriptionView::switchItem(const QModelIndex &previous, const QModelIndex &current)
{
    try{
        data->setDescription(previous, document()->toHtml());
        document()->setHtml(data->getDescription(current));
        setEnabled(true);
    }
    catch(...){
        setDisabled(true);
        cout << "exception " << endl;
    }
}
