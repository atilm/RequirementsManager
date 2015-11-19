#ifndef HTMLTEMPLATE_H
#define HTMLTEMPLATE_H

#include <QString>
#include <QMap>
#include "qfileadapter.h"
#include "qtextstreamadapter.h"

class HtmlTemplate
{
public:
    HtmlTemplate(QFileAdapter *_inFile,
                 QTextStreamAdapter *_inStream);
    virtual ~HtmlTemplate();

    virtual void initialize(const QString &templatePath);
    virtual void setField(const QString &key, const QString &value);
    virtual void setField(const QString &key, int value);
    virtual QString getHtml();

private:
    QFileAdapter *inFile;
    QTextStreamAdapter *inStream;
    QString templateString;
    QMap<QString,QString> fields;
};

#endif // HTMLTEMPLATE_H
