#include "cppreader.h"
#include "classnode.h"
#include "functionnode.h"

#include <QDebug>
#include <QDir>
#include <QFileInfoList>

CppReader::CppReader(QFileAdapter *file, QTextStreamAdapter *inStream)
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

void CppReader::readTestSpecification(DirectoryListModel *testDirs)
{
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
    }
}

bool CppReader::atClassBegin()
{
    bool isCandidate = currentLine.startsWith("class") || currentLine.startsWith("struct");

    // discard forward declarations of classes
    if( isCandidate && !(currentLine.endsWith(";")))
        return true;
    else
        return false;
}

void CppReader::parseClass()
{
    ClassNode *classNode = new ClassNode();

    classNode->setName(extractClassName());

    QModelIndex classIdx = model->appendClass(classNode);

    while(!inStream->atEnd()){
        currentLine = inStream->readLine().trimmed();

        if(currentLine.startsWith("class") || currentLine.startsWith("struct"))
            parseClass();
        else if(currentLine.contains("("))
            parseFunction(classIdx);
    }
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


