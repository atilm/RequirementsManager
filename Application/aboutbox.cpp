#include "aboutbox.h"
#include "version.h"

#include "ui_aboutbox.h"
#include <QDebug>

AboutBox::AboutBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutBox)
{
    ui->setupUi(this);
    setWindowTitle(tr("About Requirements Manager"));

    QString content = QString(
                "<html>"
                "<p>Version: %1</p>"
                "<h1>Project Home:</h1>"
                "<a href=\"https://github.com/atilm/RequirementsManager\">https://github.com/atilm/RequirementsManager</a>"
                "<h1>MIT License</h1>"
                "<p>Copyright (c) 2016 Andreas Thielmann</p>"
                "<p>Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the \"Software\"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:</p>"
                "<p>The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.</p>"
                "<p>THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.</p>"
                "</html>").arg(Version::versionNumberString());

    ui->textEdit->setHtml(content);
    ui->textEdit->setReadOnly(true);
}

AboutBox::~AboutBox()
{
    delete ui;
}
