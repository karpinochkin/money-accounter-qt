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

    virtual bool isCorrect() const {
        return !(id < 1);
    }
};

}

using MBase = Models::Base;

#endif // BASEMODEL_H
