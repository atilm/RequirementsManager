#ifndef QPLAINTEXTEDITADAPTER_H
#define QPLAINTEXTEDITADAPTER_H

#include <QPlainTextEdit>

class QPlainTextEditAdapter : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit QPlainTextEditAdapter(QWidget *parent = 0);
    virtual ~QPlainTextEditAdapter();

signals:

public slots:

};

#endif // QPLAINTEXTEDITADAPTER_H
