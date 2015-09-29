#include "gtest/gtest.h"
#include "appsettings.h"
#include "randomdatagenerator.h"
using namespace std;

class AppSettingsTests : public ::testing::Test{
protected:
    AppSettings *settings;
    RandomDataGenerator rand;

    QString defaultDir;

    AppSettingsTests(){
        settings = new AppSettings();

        defaultDir = ".";
    }

    virtual ~AppSettingsTests(){
        delete settings;
    }
};

TEST_F(AppSettingsTests, clear_resets_file_start_directory){
    QString dirPath = rand.getQString(20,1);

    settings->setDirectory(dirPath);
    settings->clear();

    EXPECT_EQ(defaultDir, settings->directory());
}

TEST_F(AppSettingsTests, file_start_directory_is_saved_and_loaded){
    QString dirPath = rand.getQString(20,1);

    settings->setDirectory(dirPath);
    settings->save();
    settings->clear();
    settings->load();

    EXPECT_EQ(dirPath, settings->directory());
}
