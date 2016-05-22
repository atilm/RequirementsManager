#ifndef QLINEEDITADAPTER_H
#define QLINEEDITADAPTER_H

#include <QLineEdit>

class QLineEditAdapter : public QLineEdit
{
    Q_OBJECT
public:
    explicit QLineEditAdapter(QWidget *parent = 0);
    virtual ~QLineEditAdapter();

signals:

public slots:

};

#endif // QLINEEDITADAPTER_H
