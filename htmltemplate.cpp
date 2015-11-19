#include "htmltemplate.h"
#include <QFile>

HtmlTemplate::HtmlTemplate(QFileAdapter *_inFile, QTextStreamAdapter *_inStream)
{
    inFile = _inFile;
    inStream = _inStream;
}

HtmlTemplate::~HtmlTemplate()
{
    delete inFile;
    delete inStream;
}

void HtmlTemplate::initialize(const QString &templatePath)
{
    inFile->setFileName(templatePath);

    if (!inFile->open(QIODevice::ReadOnly | QIODevice::Text)){
        templateString = QString("<!-- MISSING TEMPLATE FILE: %1 -->").arg(templatePath);
        return;
    }

    inStream->setDevice(inFile);
    templateString = inStream->readAll();
}

void HtmlTemplate::setField(const QString &key, const QString &value)
{
    QString fullKey = QString("<!--") + key + QString("-->");
    fields[fullKey] = value;
}

void HtmlTemplate::setField(const QString &key, int value)
{
    setField(key, QString::number(value));
}

QString HtmlTemplate::getHtml()
{
    QString copy = templateString;

    foreach(QString key, fields.keys()){
        QString value = fields.value(key);
        copy.replace(key, value);
    }

    return copy;
}
