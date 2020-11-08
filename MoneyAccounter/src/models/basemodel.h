#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QString>
#include <QList>

namespace Models {

///
/// \brief The Base class - parent model class
///
class Base {
public:
    virtual ~Base() = default;
    uint id {};

    virtual bool isCorrect() const = 0; /// full model checking
    virtual bool isCorrectDB() const = 0; /// db model checking
};

}

#endif // BASEMODEL_H
