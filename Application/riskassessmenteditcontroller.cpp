#include "riskassessmenteditcontroller.h"
#include <QDebug>
#include <QMessageBox>

RiskAssessmentEditController::RiskAssessmentEditController(RiskAssessmentDialog *dialog, PreventiveActionDialog *actionDialog) :
    QObject(0)
{
    riskModel = nullptr;
    riskView = nullptr;
    this->dialog = dialog;
    this->actionDialog = actionDialog;
}

RiskAssessmentEditController::~RiskAssessmentEditController()
{
    delete dialog;
    delete actionDialog;
}

void RiskAssessmentEditController::setRequirementsModel(shared_ptr<RequirementsModel> requirements)
{
    this->reqModel = requirements;
}

void RiskAssessmentEditController::setRequirementsView(RequirementsView *reqView)
{
    this->reqView = reqView;
    connect(reqView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(currentRequirementChanged(QModelIndex,QModelIndex)));
}

void RiskAssessmentEditController::setRiskModel(shared_ptr<RiskAssessmentModel> model)
{
    this->riskModel = model;
    dialog->setModel(model);
}

void RiskAssessmentEditController::setRiskView(RiskTableView *view)
{
    this->riskView = view;
    connect(riskView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(riskClicked(QModelIndex)));
    connect(view, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(editRiskAssessment(QModelIndex)));
}

void RiskAssessmentEditController::setAddRiskButton(QToolButton *addRiskButton)
{
    connect(addRiskButton, SIGNAL(clicked()), this, SLOT(insertBeforeCurrent()));
}

void RiskAssessmentEditController::setRemoveRiskButton(QToolButton *removeRiskButton)
{
    connect(removeRiskButton, SIGNAL(clicked()), this, SLOT(removeCurrent()));
}

void RiskAssessmentEditController::setActionView(PreventiveActionTableView *actionView)
{
    this->actionView = actionView;
    connect(actionView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(actionClicked(QModelIndex)));
    connect(actionView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(editPreventiveAction(QModelIndex)));
}

void RiskAssessmentEditController::setAddActionButton(QToolButton *addActionButton)
{
    connect(addActionButton, SIGNAL(clicked()), this, SLOT(insertActionBeforeCurrent()));
}

void RiskAssessmentEditController::setRemoveActionButton(QToolButton *removeActionButton)
{
    connect(removeActionButton, SIGNAL(clicked()), this, SLOT(removeCurrentAction()));
}

void RiskAssessmentEditController::setDescriptionView(RiskDescriptionView *descriptionView)
{
    this->descriptionView = descriptionView;
    descriptionView->setReadOnly(true);
}

void RiskAssessmentEditController::currentRequirementChanged(const QModelIndex &current, const QModelIndex &)
{
    try{
        riskModel = reqModel->getRiskAssessment(current);
        riskView->setModel(riskModel.get());
        riskView->resizeColumnsToContents();
        dialog->setModel(riskModel);
        actionView->setModel(nullptr);
        descriptionView->clearDisplay();
        connect(riskView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                this, SLOT(currentRiskChanged(QModelIndex,QModelIndex)));
    }
    catch(const InvalidIndexException &){

    }
}

void RiskAssessmentEditController::currentRiskChanged(const QModelIndex &current, const QModelIndex &)
{
    try{
        actionModel = riskModel->getPreventiveActions(current);
        actionView->setModel(actionModel);
        actionView->resizeColumnsToContents();
        actionDialog->setModel(actionModel);
        descriptionView->displayRisk(riskModel->getRiskAssessment(current));
        connect(actionView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                this, SLOT(currentActionChanged(QModelIndex, QModelIndex)));
    }
    catch(const runtime_error &){
        descriptionView->clear();
    }
}

void RiskAssessmentEditController::currentActionChanged(const QModelIndex &current, const QModelIndex &)
{
    try{
        PreventiveAction *a = actionModel->getAction(current);
        descriptionView->displayAction(a);
    }
    catch(const runtime_error &e){
        descriptionView->clear();
    }
}

void RiskAssessmentEditController::insertBeforeCurrent()
{
    if(riskModel){
        riskModel->add(riskView->currentIndex().row());
        riskView->resizeColumnsToContents();
    }
}

void RiskAssessmentEditController::removeCurrent()
{
    if(riskModel){
        riskModel->remove(riskView->currentIndex());
        riskView->resizeColumnsToContents();
    }
}

void RiskAssessmentEditController::insertActionBeforeCurrent()
{
    if(actionModel){
        actionModel->add(actionView->currentIndex().row());
        actionView->resizeColumnsToContents();
    }
}

void RiskAssessmentEditController::removeCurrentAction()
{
    if(actionModel){
        actionModel->remove(actionView->currentIndex());
        actionView->resizeColumnsToContents();
    }
}

void RiskAssessmentEditController::editRiskAssessment(const QModelIndex &index)
{
    if(riskModel){
        dialog->exec(index);
        descriptionView->displayRisk(riskModel->getRiskAssessment(riskView->currentIndex()));
    }
}

void RiskAssessmentEditController::editPreventiveAction(const QModelIndex &index)
{
    if(!actionModel)
        return;

    PreventiveAction *action = actionModel->getAction(actionView->currentIndex());

    if(action->isReference()){
        QMessageBox::information(0, tr("Edit preventive action"),
                                 tr("References to automated tests are not editable."));
    }
    else{
        actionDialog->exec(index);
        descriptionView->displayAction(action);
    }
}

void RiskAssessmentEditController::actionClicked(const QModelIndex &index)
{
    if(index.isValid())
        descriptionView->displayAction(actionModel->getAction(index));
}

void RiskAssessmentEditController::riskClicked(const QModelIndex &index)
{
    if(index.isValid())
        descriptionView->displayRisk(riskModel->getRiskAssessment(index));
}

void RiskAssessmentEditController::handleFileLoad()
{
    descriptionView->clear();
    riskView->setModel(nullptr);
    actionView->setModel(nullptr);
}
