#ifndef TAGEXTRACTOR_H
#define TAGEXTRACTOR_H

#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QVector>

class TagExtractor
{
public:
    TagExtractor(const QString &contents = "");
    virtual ~TagExtractor();

    virtual void setContents(const QString &contents);
    virtual QStringList getAllInTag(const QString &tag);
    virtual QString getFirstInTag(const QString &tag);
    virtual QStringList getAllInDelimiters(const QString &start, const QString &end);

private:
    QString contents;
    QStringList subContents;
    QString startTag;
    QString endTag;
    QVector<int> starts;
    QVector<int> ends;

    QVector<int> findAll(const QString &s);
    QVector<int> findAllWholeWords(const QString &s);
    void findStartEndPositions(const QString &tag);
    void extractSubContents();
    void initializeTags(const QString &tag);
    QString extract(int start, int end);
};

#endif // TAGEXTRACTOR_H
