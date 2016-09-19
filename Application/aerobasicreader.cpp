#include "aerobasicreader.h"
#include "classnode.h"
#include "functionnode.h"
#include "tagextractor.h"
#include "testnode.h"

#include <QDebug>
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
    readTestSpecification(testDirs);

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

void AerobasicReader::readTestSpecification(DirectoryListModel *testDirs)
{
    for(int i=0;i<testDirs->rowCount();i++)
        parseTestFilesInDirectory(testDirs->absolutePath(i));
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

    QString shortDesc = removeCommentsFromLineStart(extractor.getFirstInTag("short"), ";");

    functionNode->setDescription(shortDesc);

    model->insertFunctionAlphabetically(parent, functionNode);
}

void AerobasicReader::parseTestFilesInDirectory(const QString &dirPath)
{
    QStringList fileInCurrentDir = listSourceFiles(dirPath);

    foreach(QString filePath, fileInCurrentDir)
        extractTestsFromFile(filePath);

    testFiles += fileInCurrentDir;
}

void AerobasicReader::extractTestsFromFile(const QString &filePath)
{
    if(!openStream(filePath))
        return;

    parseTestDefinitionFile(filePath);

    file->close();
}

void AerobasicReader::parseTestDefinitionFile(const QString &filePath)
{
    extractTestCase(filePath);

    TagExtractor extractor(inStream->readAll());

    QStringList testDefinitions = extractor.getAllInDelimiters("DFS", "ENDDFS");

    foreach(QString definition, testDefinitions){
        parseTestDefinition(definition);
    }
}

void AerobasicReader::extractTestCase(const QString &filePath)
{
    QFileInfo fInfo(filePath);
    currentTestCase = fInfo.baseName();
}

void AerobasicReader::parseTestDefinition(const QString &definition)
{
    TagExtractor extractor(definition);

    SourceAddress address;
    TestNode *testNode = new TestNode();

    address.className = extractor.getFirstInTag("file").trimmed();
    address.functionName = extractor.getFirstInTag("function").trimmed();

    testNode->setTestCase(currentTestCase);
    testNode->setTestName(extractTestName(definition));

    QString shortDesc = removeCommentsFromLineStart(extractor.getFirstInTag("short"), ";");
    QString preparation = removeCommentsFromLineStart(extractor.getFirstInTag("preparation"), ";");
    QString action = removeCommentsFromLineStart(extractor.getFirstInTag("action"), ";");
    QString result = removeCommentsFromLineStart(extractor.getFirstInTag("result"), ";");

    testNode->appendToShortDescription(shortDesc);
    testNode->appendToPreparation(preparation);
    testNode->appendToAction(action);
    testNode->appendToResult(result);

    model->appendTest(address, testNode);
}

QString AerobasicReader::extractTestName(const QString &definition)
{
    int lineEnd = definition.indexOf("\n");
    return definition.mid(0, lineEnd).trimmed();
}

QString AerobasicReader::removeCommentsFromLineStart(const QString &s,
                                                     const QString &commentStr)
{
    QStringList lines = s.split("\r\n");

    QString outLines;

    foreach(QString line, lines){
        line = line.trimmed();
        if(line.startsWith(commentStr)){
            outLines.append(line.replace(0, commentStr.size(), "") + "\r\n");
        }
        else{
            outLines.append(line + "\r\n");
        }
    }

    return outLines;
}
