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

    void operator<<(QSqlQuery *query) {
        id = query->value(0).toUInt();
        path = query->value(1).toString();
    }
};

}

using MIcon = Models::Icon;
using MIcons = QList<Models::Icon>;

#endif // ICON_H
