#include "tagextractor.h"
#include <QRegExp>

TagExtractor::TagExtractor(const QString &content)
{
    this->contents = content;
}

TagExtractor::~TagExtractor()
{

}

void TagExtractor::setContents(const QString &contents)
{
    this->contents = contents;
}

QStringList TagExtractor::getAllInTag(const QString &tag)
{
    findStartEndPositions(tag);

    extractSubContents();

    return subContents;
}

QString TagExtractor::getFirstInTag(const QString &tag)
{
    initializeTags(tag);

    int start = contents.indexOf(startTag, 0);
    int end = contents.indexOf(endTag, 0);

    QString contents;

    if(start != -1 && end != -1)
        contents = extract(start, end);

    return contents;
}

QStringList TagExtractor::getAllInDelimiters(const QString &start, const QString &end)
{
    startTag = start;
    endTag = end;

    starts = findAllWholeWords(startTag);
    ends = findAllWholeWords(endTag);

    extractSubContents();

    return subContents;
}

void TagExtractor::findStartEndPositions(const QString &tag)
{
    initializeTags(tag);

    starts = findAll(startTag);
    ends = findAll(endTag);
}

void TagExtractor::extractSubContents()
{
    for(int i=0;i<starts.count();i++){
        subContents.append( extract(starts[i], ends[i]) );
    }
}

void TagExtractor::initializeTags(const QString &tag)
{
    startTag = QString("<%1>").arg(tag);
    endTag = QString("</%1>").arg(tag);
}

QString TagExtractor::extract(int start, int end)
{
    int first = start + startTag.length();
    int count = end - first;

    return contents.mid(first, count);
}

QVector<int> TagExtractor::findAll(const QString &s)
{
    QVector<int> positions;

    int next = contents.indexOf(s, 0);

    while(next != -1){
        positions.append(next);
        int current = next;
        next = contents.indexOf(s, current + s.length());
    }

    return positions;
}

QVector<int> TagExtractor::findAllWholeWords(const QString &s)
{
    QString pattern = QString("\\b%1\\b").arg(s);
    QRegExp re(pattern);

    QVector<int> positions;

    int next = contents.indexOf(re, 0);

    while(next != -1){
        positions.append(next);
        int current = next;
        next = contents.indexOf(re, current + re.matchedLength());
    }

    return positions;
}


