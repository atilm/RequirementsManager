#ifndef DESCRIPTIONVIEW_H
#define DESCRIPTIONVIEW_H

#include <QTextEdit>
#include "requirementsmodel.h"

class DescriptionView : public QTextEdit
{
    Q_OBJECT
public:
    explicit DescriptionView(QWidget *parent = 0);

    void setModel(RequirementsModel *data);

signals:

public slots:

    void switchItem(const QModelIndex &current, const QModelIndex &previous);

private:
    QTextDocument *defaultDocument;
    RequirementsModel *data;

    void initialize();
};

#endif // DESCRIPTIONVIEW_H
