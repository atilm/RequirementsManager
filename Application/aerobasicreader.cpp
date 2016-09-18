#include "aerobasicreader.h"

AerobasicReader::AerobasicReader(QFileAdapter *file,
                                 QTextStreamAdapter *inStream,
                                 shared_ptr<DirectoryLister> dirLister)
{
    this->file = file;
    this->inStream = inStream;
    this->dirLister = dirLister;
}

AerobasicReader::~AerobasicReader()
{
    delete file;
    delete inStream;
}

QString AerobasicReader::language() const
{
    return "A3200";
}

SourceCodeModel *AerobasicReader::parseSourceCode(DirectoryListModel *sourceDirs,
                                                  DirectoryListModel *testDirs)
{
    model = new SourceCodeModel();
    headerFiles.clear();
    testFiles.clear();

    readDesignSpecification(sourceDirs);
    //readTestSpecification(testDirs);

    return model;
}

QStringList AerobasicReader::getFilePaths() const
{
    return headerFiles + testFiles;
}

void AerobasicReader::readDesignSpecification(DirectoryListModel *sourceDirs)
{

}
