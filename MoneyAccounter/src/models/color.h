#ifndef COLOR_H
#define COLOR_H

#include <ctype.h>
#include <algorithm>
#include <QColor>
#include <QDebug>

namespace Models {

class ColorErrorException : public std::exception {
public:
    explicit ColorErrorException() noexcept = default;
    ~ColorErrorException() throw() = default;

    virtual const char* what() const throw () {
        return "invalid color string";
    }
};

class Color {
public:
    explicit Color(const QString& colorString) {
        setColorFromString(colorString);
    }
    explicit Color(const QColor& color) : color(color) {

    }
    explicit Color() {
        color.setNamedColor("#000000");
    }

    ~Color() = default;

    QString hex() const {
        return color.name(QColor::HexRgb);
    }

    void set(const QColor& color) {
        this->color = color;
    }

    void set(const QString &colorString) {
        setColorFromString(colorString);
    }

private:
    QColor color;
    void isColorStringCheck(QString colorString) {
        if (colorString.at(0) != "#") {
            throw ColorErrorException();
        }
        if (std::size(colorString) != 7) {
            throw ColorErrorException();
        }

        auto res = std::all_of(std::begin(colorString) + 1, std::end(colorString), [](QChar c){ return std::isxdigit(c.toLatin1()); });

        if (!res) {
            throw  ColorErrorException();
        }
    }

    void setColorFromString(const QString& colorString) {
        try {
            isColorStringCheck(colorString);
            color.setNamedColor(colorString);
        } catch (const ColorErrorException& err) {
            qDebug() << err.what();
        }
    }
};
}

#endif // COLOR_H
