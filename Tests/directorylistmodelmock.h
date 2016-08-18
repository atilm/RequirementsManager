#ifndef DIRECTORYLISTMODELMOCK
#define DIRECTORYLISTMODELMOCK

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "directorylistmodel.h"

class DirectoryListModelMock : public DirectoryListModel {
 public:

    DirectoryListModelMock() : DirectoryListModel(nullptr, 0) {}

    MOCK_METHOD0(clear, void ());
    MOCK_CONST_METHOD3(headerData, QVariant (int section, Qt::Orientation orientation, int role));
    MOCK_CONST_METHOD1(rowCount, int (const QModelIndex &parent));
    MOCK_CONST_METHOD2(data, QVariant (const QModelIndex &index, int role));
    MOCK_CONST_METHOD1(absolutePath, QString (int idx));
    MOCK_METHOD1(add, void (const QString &directoryPath));
    MOCK_METHOD1(remove, bool (const QModelIndex &index));
};

#endif // DIRECTORYLISTMODELMOCK

