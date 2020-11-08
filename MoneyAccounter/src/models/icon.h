#ifndef ICON_H
#define ICON_H

#include "basemodel.h"

namespace Models {

class Icon : public Base {
public:
    QString path;

    bool isCorrect() const override {
        return !(id < 1 || path.isEmpty());
    }

    bool isCorrectDB() const override {
        return isCorrect();
    }
};

}

#endif // ICON_H
