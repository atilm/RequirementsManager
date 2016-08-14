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
                "<a href=\https://github.com/atilm/TaskBoard\">https://github.com/atilm/TaskBoard</a>"
                "<h1>GNU General Public License</h1>"
                "<p>Copyright (C) 2016  Andreas Thielmann</p>"
                "<p>This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.</p>"
                "<p>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.</p>"
                "<p>You should have received a copy of the GNU General Public License along with this program.  If not, see <a href=\"http://www.gnu.org/licenses/\">http://www.gnu.org/licenses/</a>.</p>"
                "</html>").arg(Version::versionNumberString());

    ui->textEdit->setHtml(content);
    ui->textEdit->setReadOnly(true);
}

AboutBox::~AboutBox()
{
    delete ui;
}
