#include "qparser.h"

QParser::QParser(QObject *parent)
    : QObject(parent)
{

}

QList<KIDRow> QParser::ParseKID(const QString &path)
{
    kid = std::make_unique<QKIDParser>(this);
    return kid->Parse(path);
}

QStringList QParser::ParseQRC(const QString &path, const QString &key)
{
    qrc = std::make_unique<QQRCParser>(this);
    return qrc->Parse(path, key);
}


QKIDParser::QKIDParser(QObject *parent)
    : QBaseParser(parent)
{

}

QList<KIDRow> QKIDParser::Parse(const QString &path)
{
    QFile file(path);
    openFileReadOnly(file); // open file

    return getKIDRow(file.readAll());
}

QList<QStringList> QKIDParser::getObjectsInRows(const QStringList& rows)
{
    QList<QStringList> objectsInRow;
    for (auto row : rows) { // every row
        objectsInRow.push_back(splitBySemicolon(row)); // get every object list in every row by split ;
    }
    return objectsInRow;
}

bool QKIDParser::isArray(const QString &s)
{
    return s.contains("[{") && s.contains("}]");
}

void QKIDParser::arrayProccessing(QString& object, KIDRow& row)
{
    /// действия с массивом
    object = selectArrayContent(object);
    auto arrayItems = splitByEllipsis(object);

    QList<KIDObject> array;
    for (auto item : arrayItems) {
        array.push_back(KIDObject{item});
    }
    row.array_objects.push_back(array);
}

KIDRow QKIDParser::rowObjectsProcessing(const QStringList& rowObjects)
{
    KIDRow row;
    for (auto object : rowObjects) {
        if (isArray(object)) { // if object is array
            arrayProccessing(object, row);
        }
        else {
            objectAdding(object, row); // if object is not array
        }
    }
    return row;
}

void QKIDParser::objectAdding(QString& object, KIDRow &row)
{
    row.objects.push_back(KIDObject{object});
}

QString QKIDParser::selectArrayContent(const QString &s)
{
    QRegExp rx("\\[\\{(.+)\\}\\]");
    rx.setMinimal(true);
    rx.indexIn(s);
    return rx.cap(1);
}

QList<KIDRow> QKIDParser::getKIDRow(const QString &text)
{
    QList<KIDRow> output;
    auto rows = splitByRow(text); // get rows
    auto objectsInRows = getObjectsInRows(rows); // get every object in every row

    for (auto objects : objectsInRows) {
        output.push_back(rowObjectsProcessing(objects)); // fill output list
    }
    return output;
}

QQRCParser::QQRCParser(QObject *parent)
    : QBaseParser(parent)
{

}

QStringList QQRCParser::Parse(const QString &path, const QString &key)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        throw ExceptionParser("error open file");
    }

    auto rows = splitByRow(file.readAll());
    this->removeIncorrectStrings(rows, key);
    this->selectPath(rows);

    return rows;
}

void QQRCParser::removeIncorrectStrings(QStringList &list, const QString& key)
{
    list.erase(std::remove_if(std::begin(list), std::end(list), [&key](auto &it){ return !it.contains(key); }),
               std::end(list));
}

void QQRCParser::selectPath(QStringList &list)
{
    QRegExp rx("\\<file\\>(.+)\\<\\/file\\>");
    for(auto &l : list) {
        rx.setMinimal(true);
        rx.indexIn(l);
        l = rx.cap(1);
    }
}
