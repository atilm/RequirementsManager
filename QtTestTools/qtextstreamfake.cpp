#include "qtextstreamfake.h"

QTextStreamFake::QTextStreamFake()
{

}

QTextStreamFake::~QTextStreamFake()
{

}

void QTextStreamFake::setLines(const QStringList &list)
{
    lines = list;
}

bool QTextStreamFake::atEnd() const
{
    return lines.isEmpty();
}

QString QTextStreamFake::readLine()
{
    return lines.takeFirst();
}

QString QTextStreamFake::readAll()
{
    return lines.join("\n");
}

void QTextStreamFake::setDevice(QFileAdapter *)
{
    //does nothing
}

void QTextStreamFake::write(const QString &)
{
    //does nothing
}
