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
using Query = std::shared_ptr<QSqlQuery>;

///
/// \brief The QBase class - abstract base db tables class
///
class QBase : public QObject
{
public:
    ~QBase();
    Query MakeQuery(const QString &textQuery);
    Query MakeQuery(const QString &textQuery,
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
    uint getCorrectID(const MBase& model, const QString &tableName, const QString &idColumnName);

    template<typename T> QVariantList getAllRows(QSqlQuery* query) {
        QVariantList list;
        while(query->next()) {
            T m;
            m << query;
            list.push_back(QVariant::fromValue(m));
        }
        return list;
    }

    template<typename T> Ref<T> getRow(QSqlQuery *query) {
        auto output = CreateRef<T>();
        if(query->next()) {
            *output << query;
        }
        return output;
    }

private:
    QMutex *mutex = nullptr;
    QSqlDatabase db;

    QueryBool execQuery(const QString &textQuery);
    QueryBool execQuery(const QString &textQuery,
                        const QString &bindName,
                        QVariant bindValue);
    inline void checkDatabaseValid() const;
    void openDatabaseIfNotOpened();
};


}

#endif // BASE_H
