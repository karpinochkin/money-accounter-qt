#ifndef ICON_H
#define ICON_H

#include <QString>

namespace Models {

class Icon {
public:
    uint id;
    QString path;

    bool isCorrect() const {
        return !(id < 1 || path.isEmpty());
    }
};
}

#endif // ICON_H
