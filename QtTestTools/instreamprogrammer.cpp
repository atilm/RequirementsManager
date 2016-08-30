#include "gmock/gmock.h"
#include "instreamprogrammer.h"
using ::testing::Return;

void InStreamProgrammer::prepareSream(QTextStreamAdapterMock *stream,
                                      const QStringList &lines,
                                      Sequence seq,
                                      int fileEndAfterNLines)
{
    QListIterator<QString> it(lines);
    it.toBack();

    while(it.hasPrevious()){
        QString s = it.previous();

        EXPECT_CALL(*stream, readLine())
                .InSequence(seq)
                .WillOnce(Return(s));
    }

    if(fileEndAfterNLines != -1){
        EXPECT_CALL(*stream, atEnd())
                .Times(fileEndAfterNLines)
                .WillOnce(Return(false))
                .WillRepeatedly(Return(true));
    }
    else{
        EXPECT_CALL(*stream, atEnd())
                .WillRepeatedly(Return(false));
    }
}

