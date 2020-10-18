#ifndef QPARSER_H
#define QPARSER_H

#include <QString>
#include <QObject>
#include <QFile>
//#include <QDebug>
#include <memory>
#include <QRegExp>
#include <algorithm>

class QKIDParser;
class QQRCParser;

struct KIDObject {
    QString info;
    QString operator()() const {
        return info;
    }
};

struct KIDRow {
    QList<KIDObject> objects;
    QList<QList<KIDObject>> array_objects;
};

class ExceptionParser : public std::exception {
public:
    explicit ExceptionParser(const char* message) noexcept : err(message) {

    }

    explicit ExceptionParser(const std::string& message) noexcept : err(message) {

    }

    virtual const char* what() const throw () {
        return err.c_str();
    }
    ~ExceptionParser() throw() = default;
private:
    std::string err;
};

class QParser : public QObject
{
public:
    explicit QParser(QObject *parent = nullptr);
    ~QParser() = default;

    QList<KIDRow> ParseKID(const QString &path);
    QStringList ParseQRC(const QString &path, const QString &key);

private:
    std::unique_ptr<QKIDParser> kid;
    std::unique_ptr<QQRCParser> qrc;
};

class QBaseParser : public QObject
{
public:
    ~QBaseParser() = default;

protected:
    QBaseParser(QObject *parent = nullptr) : QObject(parent) {

    }

    QStringList splitByRow(const QString &data) {
        return data.split("\n", QString::SkipEmptyParts);
    }

    QStringList splitBySemicolon(const QString &data) {
        return data.split(";", QString::SkipEmptyParts);
    }

    QStringList splitByEllipsis(const QString &data) {
        return data.split("...", QString::SkipEmptyParts);
    }

    void openFileReadOnly(QFile &file) {
        if (!file.open(QIODevice::ReadOnly)) {
            QString err = "error open file : " + file.errorString();
            throw ExceptionParser(err.toStdString().c_str());
        }
    }
};

/// object1;object2;object3;...objectN;
/// object;[{array_obj_1...array_obj_2}];
class QKIDParser : public QBaseParser
{
public:
    explicit QKIDParser(QObject *parent = nullptr);
    ~QKIDParser() = default;

    QList<KIDRow> Parse(const QString& path);

private:
    QList<QStringList> getObjectsInRows(const QStringList &rows);
    bool isArray(const QString&);
    void arrayProccessing(QString &object, KIDRow &row);
    KIDRow rowObjectsProcessing(const QStringList &rowObjects);
    void objectAdding(QString& object, KIDRow &row);
    QString selectArrayContent(const QString &);
    QList<KIDRow> getKIDRow(const QString &text);
};

/// <file>###key###</file>
class QQRCParser : public QBaseParser
{
public:
    explicit QQRCParser(QObject *parent = nullptr);
    ~QQRCParser() = default;

    QStringList Parse(const QString &path, const QString &key);

private:
    void removeIncorrectStrings(QStringList &list, const QString &key);
    void selectPath(QStringList &list);

};

#endif // QPARSER_H
