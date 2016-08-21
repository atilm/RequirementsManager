#ifndef INSTREAMPROGRAMMER_H
#define INSTREAMPROGRAMMER_H

#include "QTextStreamAdapterMock.h"

#include <QStringList>

class InStreamProgrammer
{
public:

    /*! Prepare a QTextStream mock to return a sequence of lines
     \param stream The QTextStream mock object
     \param lines QStringList of lines the mock object will return
     \param fileEndAfterNLines Number n after which to return true from atEnd()

     If n is given for fileEndAfterNLines, the function stream.atEnd() is expected
     to be called at least n times. It will return "true" for the n first calls
     and "false" for any subsequent call.

     If -1 is given for fileEndAfterNLines, the function stream.atEnd() will always
     return "false" and no minimum number of calls is expected.
     */
    static void prepareSream(QTextStreamAdapterMock *stream,
                             const QStringList &lines,
                             int fileEndAfterNLines = -1);
};

#endif // INSTREAMPROGRAMMER_H
