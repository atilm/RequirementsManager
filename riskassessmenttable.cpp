#include "riskassessmenttable.h"
#include "ui_riskassessmenttable.h"

RiskAssessmentTable::RiskAssessmentTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RiskAssessmentTable)
{
    ui->setupUi(this);
    setMinimumWidth(555);
    setMinimumHeight(190);
    ui->riskView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->riskView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->riskView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

RiskAssessmentTable::~RiskAssessmentTable()
{
    delete ui;
}

void RiskAssessmentTable::setModel(RiskModel *model)
{
    this->model = model;
    ui->riskView->setModel(model);
    ui->riskView->selectionModel()->setCurrentIndex(model->getCurrentRisk(),
                                                    QItemSelectionModel::ClearAndSelect);
    connect(ui->riskView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(handleIndexChanged(QModelIndex,QModelIndex)));
}

void RiskAssessmentTable::handleIndexChanged(const QModelIndex &current, const QModelIndex &previous)
{
    model->setCurrentRisk(current);
}
