#include "gmock/gmock.h"
#include "instreamprogrammer.h"
using ::testing::Return;

void InStreamProgrammer::prepareSream(QTextStreamAdapterMock *stream,
                                      const QStringList &lines,
                                      Sequence seq,
                                      bool noFileEnd)
{
    QListIterator<QString> it(lines);
    it.toBack();

    while(it.hasPrevious()){
        QString s = it.previous();

        EXPECT_CALL(*stream, atEnd())
                .InSequence(seq)
                .WillOnce(Return(false));

        EXPECT_CALL(*stream, readLine())
                .InSequence(seq)
                .WillOnce(Return(s));
    }

    if(noFileEnd){
        EXPECT_CALL(*stream, atEnd())
                .InSequence(seq)
                .WillRepeatedly(Return(true));
    }
    else{
        EXPECT_CALL(*stream, atEnd())
                .InSequence(seq)
                .WillRepeatedly(Return(false));
    }
}

