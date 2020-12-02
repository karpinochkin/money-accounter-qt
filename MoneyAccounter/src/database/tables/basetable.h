#ifndef BASETABLE_H
#define BASETABLE_H

#include <QtSql>
#include <tuple>
#include <string>
#include "tables.h"
#include "../../models/basemodel.h"
#include "../../core/base.h"

namespace DB {

///
/// \brief The ExceptionDB class - database exception type
///
class ExceptionDB : public std::exception {
public:
    explicit ExceptionDB(const char* message) noexcept : err(message) {

    }

    explicit ExceptionDB(const std::string& message) noexcept : err(message) {

    }

    virtual const char* what() const throw () {
        return err.c_str();
    }
    ~ExceptionDB() throw() = default;
private:
    std::string err;
};

}

namespace DB::Tables {

using QueryBool = std::tuple<std::shared_ptr<QSqlQuery>, bool>;

///
/// \brief The QBase class - abstract base db tables class
///
class QBase : public QObject
{
public:
    ~QBase();
    QueryBool MakeQuery(const QString &textQuery);
    QueryBool MakeQuery(const QString &textQuery,
                        const QString &bindName,
                        QVariant bindValue);

protected:
    QBase(QSqlDatabase &database, QObject *parent = nullptr);

    virtual void CreateTable() = 0;
    virtual void Add(const MBase& model) = 0;
    virtual void Edit(const MBase& model) = 0;
    virtual Ref<MBase> Get(uint id) = 0;
    virtual void Remove(uint id) = 0;
    virtual QVariantList GetAll() = 0;

    void removeRow(uint id, const QString &tableName, const QString &idColumnName);

private:
    QMutex *mutex = nullptr;
    QSqlDatabase db;

    QueryBool execQuery(const QString &textQuery);
    QueryBool execQuery(const QString &textQuery,
                        const QString &bindName,
                        QVariant bindValue);
    inline void printTextError(const QString &textError,
                               const QString &textQuery);
    inline void checkDatabaseValid() const;
    void openDatabaseIfNotOpened();
};


}

#endif // BASE_H
