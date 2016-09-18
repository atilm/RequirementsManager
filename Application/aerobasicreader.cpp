#include "aerobasicreader.h"
#include "classnode.h"
#include "functionnode.h"
#include "tagextractor.h"
#include "testnode.h"

#include <QFileInfo>

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
    sourceFiles.clear();
    testFiles.clear();

    readDesignSpecification(sourceDirs);
    //readTestSpecification(testDirs);

    return model;
}

QStringList AerobasicReader::getFilePaths() const
{
    return sourceFiles + testFiles;
}

void AerobasicReader::readDesignSpecification(DirectoryListModel *sourceDirs)
{
    for(int i=0;i<sourceDirs->rowCount();i++)
        parseSourceFilesInDirectory(sourceDirs->absolutePath(i));
}

void AerobasicReader::parseSourceFilesInDirectory(const QString &dirPath)
{
    QStringList filesInCurrentDir = listSourceFiles(dirPath);

    foreach(QString filePath, filesInCurrentDir)
        extractFunctionsFromFile(filePath);

    sourceFiles += filesInCurrentDir;
}

QStringList AerobasicReader::listSourceFiles(const QString &dirPath)
{
    return dirLister->listFiles(dirPath, ".+\\.(pou|pgm)");
}

void AerobasicReader::extractFunctionsFromFile(const QString &filePath)
{
    if(!openStream(filePath))
        return;

    parseSourceLines(filePath);

    file->close();
}

bool AerobasicReader::openStream(const QString &filePath)
{
    file->setFileName(filePath);
    if (!file->open(QIODevice::ReadOnly))
        return false;

    inStream->setDevice(file);
    return true;
}

void AerobasicReader::parseSourceLines(const QString &filePath)
{
    ClassNode *classNode = new ClassNode();

    classNode->setName(extractModuleName(filePath));
    // classNode->setDescription(); No description in files

    QModelIndex classIdx = model->insertClassAlphabetically(classNode);

    TagExtractor extractor(inStream->readAll());
    QStringList functionDefinitions = extractor.getAllInTag("function");

    foreach(QString definition, functionDefinitions){
        parseFunctionDefinition(classIdx, definition);
    }
}

QString AerobasicReader::extractModuleName(const QString &filePath)
{
    QFileInfo fInfo(filePath);
    return fInfo.baseName();
}

void AerobasicReader::parseFunctionDefinition(const QModelIndex &parent,
                                              const QString &definition)
{
    TagExtractor extractor(definition);

    FunctionNode *functionNode = new FunctionNode();
    functionNode->setName(extractor.getFirstInTag("name"));
    functionNode->setDescription(extractor.getFirstInTag("short"));

    model->insertFunctionAlphabetically(parent, functionNode);
}
