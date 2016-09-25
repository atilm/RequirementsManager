#include "reporttypechooserdialog.h"
#include "ui_reporttypechooserdialog.h"

ReportTypeChooserDialog::ReportTypeChooserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportTypeChooserDialog)
{
    ui->setupUi(this);

    setWindowTitle(tr("Generate Report"));

    connect(ui->typeComboBox, SIGNAL(currentTextChanged(QString)),
            this, SLOT(updateDescription()));
}

ReportTypeChooserDialog::~ReportTypeChooserDialog()
{
    delete ui;
}

void ReportTypeChooserDialog::setGeneratorProvider(ReportGeneratorProvider *provider)
{
    this->generatorProvider = provider;

    ui->typeComboBox->clear();

    foreach (QString s, provider->availableGenerators()) {
        ui->typeComboBox->addItem(s);
    }
}

QString ReportTypeChooserDialog::getType() const
{
    return ui->typeComboBox->currentText();
}

void ReportTypeChooserDialog::updateDescription()
{
    QString type = ui->typeComboBox->currentText();
    ui->descriptionLabel->setText(generatorProvider->getDescription(type));
}
