#include "requirementrefview.h"

RequirementRefView::RequirementRefView(QWidget *parent)
    : QListWidget(parent)
{
    model = nullptr;
    addItem("Test");
}

RequirementRefView::~RequirementRefView()
{

}

void RequirementRefView::setModel(shared_ptr<RequirementsModel> model)
{
    this->model = model;
}

void RequirementRefView::switchItem(const QModelIndex &current, const QModelIndex &)
{
    showItem(current);
}

void RequirementRefView::showItem(const QModelIndex &index)
{
    if(!model){
        throw runtime_error("RequirementsRefView: No model set!");
    }

    if(index.isValid()){
        setReferenceList(model->getRequirement(index)->getReferenceList());
    }
}

void RequirementRefView::setReferenceList(QList<Requirement *> refs)
{
    clear();

    foreach(Requirement *ref, refs){
        addItem(ref->getParent()->getNumberedTitle());
    }
}
