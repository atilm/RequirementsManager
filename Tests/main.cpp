#include <stdio.h>
#include <QtCore/QCoreApplication>
#include <QApplication>

#include "gtest/gtest.h"
#include "gmock/gmock.h"


GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from gtest_main.cc\n");
  QApplication a(argc,argv);

  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
