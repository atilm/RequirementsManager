#ifndef REPORTTYPECHOOSERDIALOG_H
#define REPORTTYPECHOOSERDIALOG_H

#include <QDialog>
#include <QString>
#include <QStringList>

#include "reportgeneratorfactory.h"

namespace Ui {
class ReportTypeChooserDialog;
}

class ReportTypeChooserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReportTypeChooserDialog(QWidget *parent = 0);
    virtual ~ReportTypeChooserDialog();

    virtual void setGeneratorProvider(ReportGeneratorProvider *provider);
    virtual QString getType() const;

private:
    Ui::ReportTypeChooserDialog *ui;
    ReportGeneratorProvider *generatorProvider;

private slots:
    void updateDescription();
};

#endif // REPORTTYPECHOOSERDIALOG_H
