#include "cppreader.h"
#include "classnode.h"
#include "functionnode.h"
#include "testnode.h"

#include <QDebug>
#include <QDir>
#include <QFileInfoList>

CppReader::CppReader(QFileAdapter *file,
                     QTextStreamAdapter *inStream)
{
    model = nullptr;
    this->file = file;
    this->inStream = inStream;
}

CppReader::~CppReader()
{
    delete file;
    delete inStream;
}

QString CppReader::language() const
{
    return "C++";
}

SourceCodeModel *CppReader::parseSourceCode(DirectoryListModel *sourceDirs,
                                            DirectoryListModel *testDirs)
{
    model = new SourceCodeModel();

    readDesignSpecification(sourceDirs);
    readTestSpecification(testDirs);

    return model;
}

void CppReader::readDesignSpecification(DirectoryListModel *sourceDirs)
{
    for(int i=0;i<sourceDirs->rowCount();i++)
        parseSourceFilesInDirectory(sourceDirs->absolutePath(i));
}

void CppReader::parseSourceFilesInDirectory(const QString &dirPath)
{
    QStringList headerFiles = listHeaderFiles(dirPath);

    foreach(QString filePath, headerFiles)
        extractClassesFromFile(filePath);
}

QStringList CppReader::listHeaderFiles(const QString &dirPath)
{
    QStringList headerFiles;

    QStringList nameFilters;
    nameFilters << "*.h";


    QDir dir(dirPath);
    QFileInfoList entries = dir.entryInfoList(nameFilters, QDir::Files);

    for(int f=0;f<entries.count();f++){
        QFileInfo entry = entries[f];
        if(!entry.fileName().contains("ui_"))
            headerFiles << entry.absoluteFilePath();
    }

    return headerFiles;
}

void CppReader::extractClassesFromFile(const QString &filePath)
{
    if(!openStream(filePath))
        return;

    parseSourceLines();

    file->close();
}

bool CppReader::openStream(const QString &filePath)
{
    file->setFileName(filePath);
    if (!file->open(QIODevice::ReadOnly))
        return false;

    inStream->setDevice(file);
    return true;
}

void CppReader::parseSourceLines()
{
    while(!inStream->atEnd()){
        currentLine = inStream->readLine().trimmed();

        if(atClassBegin())
            parseClass();
        else if(currentLine.startsWith("/*!"))
            parseDesignSpecBlock();
    }
}

bool CppReader::atClassBegin()
{
    bool isCandidate = currentLine.startsWith("class");

    // discard forward declarations of classes
    if( isCandidate && !(currentLine.endsWith(";")))
        return true;
    else
        return false;
}

void CppReader::parseClass()
{
    currentScope = PRIVATE; // default scope of class is private

    ClassNode *classNode = new ClassNode();

    classNode->setName(extractClassName());
    classNode->setDescription(lineBuffer);
    lineBuffer.clear();

    QModelIndex classIdx = model->appendClass(classNode);

    while(!atClassEnd()){
        currentLine = inStream->readLine().trimmed();

        if(currentScope == PUBLIC){
            if(atClassBegin())
                parseClass();
            else if(currentLine.contains("("))
                parseFunction(classIdx);
            else if(currentLine.startsWith("/*!"))
                parseDesignSpecBlock();
        }

        if(currentLine.startsWith("public"))
            currentScope = PUBLIC;
        else if(currentLine.startsWith("private"))
            currentScope = PRIVATE;
        else if(currentLine.startsWith("protected"))
            currentScope = PROTECTED;
    }
}

bool CppReader::atClassEnd()
{
    if(currentLine.startsWith("};"))
        return true;
    else
        return false;
}

QString CppReader::extractClassName()
{
    QStringList fields = currentLine.split(QRegExp("\\s"));

    QString name;

    if(fields.count() >= 2)
        name = fields[1].trimmed();

    return name;
}

void CppReader::parseFunction(QModelIndex classIndex)
{
    FunctionNode *functionNode = new FunctionNode();

    functionNode->setName(extractFunctionName());
    functionNode->setDescription(lineBuffer);
    lineBuffer.clear();

    model->appendFunction(classIndex, functionNode);
}

QString CppReader::extractFunctionName()
{
    int endName = currentLine.indexOf("(") - 1;

    QString functionName;

    if(endName != -1){
        int startName = currentLine.lastIndexOf(" ", endName) + 1;
        int count = endName - startName + 1;
        functionName = currentLine.mid(startName, count);
    }
    else
        functionName = currentLine.trimmed();

    return functionName;
}

void CppReader::parseDesignSpecBlock()
{
    do{
        lineBuffer += currentLine.replace("/*!","").replace("*/","") + QString("\n");
        currentLine = inStream->readLine();
    } while(!currentLine.contains("*/"));
}

void CppReader::readTestSpecification(DirectoryListModel *testDirs)
{
    for(int i=0;i<testDirs->rowCount();i++)
        parseTestFilesInDirectory(testDirs->absolutePath(i));
}

void CppReader::parseTestFilesInDirectory(const QString &dirPath)
{
    QStringList testFiles = listCppFiles(dirPath);

    foreach(QString filePath, testFiles)
        extractTestsFromFile(filePath);
}

QStringList CppReader::listCppFiles(const QString &dirPath)
{
    QStringList cppFiles;

    QStringList nameFilters;
    nameFilters << "*.cpp";


    QDir dir(dirPath);
    QFileInfoList entries = dir.entryInfoList(nameFilters, QDir::Files);

    for(int f=0;f<entries.count();f++){
        QFileInfo entry = entries[f];
        cppFiles << entry.absoluteFilePath();
    }

    return cppFiles;
}

void CppReader::extractTestsFromFile(const QString &dirPath)
{
    if(!openStream(dirPath))
        return;

    parseTestDefinitionFile();

    file->close();
}

void CppReader::parseTestDefinitionFile()
{
    while(!inStream->atEnd()){
        currentLine = inStream->readLine();

        if(atTestBegin())
            parseTest();
    }
}

bool CppReader::atTestBegin()
{
    if(currentLine.contains("TEST_SPEC"))
        return true;
    else
        return false;
}

void CppReader::parseTest()
{
    TestNode *testNode = new TestNode();

    SourceAddress address = extractTestSourceAddress();

    testParsingMode = ADDRESS;

    while(!atTestEnd()){
        currentLine  = inStream->readLine();

        if(currentLine.contains("SHORT"))
            testParsingMode = SHORT;
        else if(currentLine.contains("PREPARATION"))
            testParsingMode = PREPARATION;
        else if(currentLine.contains("ACTION"))
            testParsingMode = ACTION;
        else if(currentLine.contains("RESULT"))
            testParsingMode = RESULT;
        else if(currentLine.contains("TEST_F")){
            parseTestID(testNode);
            testParsingMode = CODE;
        }
        else
            parseTestLine(testNode);
    }

    model->appendTest(address, testNode);
}

void CppReader::parseTestID(TestNode *test)
{
    test->setTestCase(extractBetween("(", ",", currentLine));
    test->setTestName(extractBetween(",", ")", currentLine));
}

SourceAddress CppReader::extractTestSourceAddress()
{
    SourceAddress a;
    a.className = extractBetween("TEST_SPEC", "::", currentLine);
    a.functionName = extractBetween("::", "(", currentLine);
    return a;
}

bool CppReader::atTestEnd()
{
    if(currentLine.startsWith("}"))
        return true;
    else
        return false;
}

void CppReader::parseTestLine(TestNode *test)
{
    switch(testParsingMode){
    case SHORT:
        test->appendToShortDescription(currentLine.trimmed());
        break;
    case PREPARATION:
        test->appendToPreparation(currentLine.trimmed());
        break;
    case ACTION:
        test->appendToAction(currentLine.trimmed());
        break;
    case RESULT:
        test->appendToResult(currentLine.replace("*/","").trimmed());
        break;
    default:
        break;
    }
}

QString CppReader::extractBetween(const QString &start,
                                  const QString &end,
                                  const QString &s)
{
    int startPos = s.indexOf(start) + start.length();
    int endPos = s.indexOf(end);
    int count = endPos - startPos;

    return s.mid(startPos, count).trimmed();
}


