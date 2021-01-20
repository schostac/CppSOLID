#include <iostream>
#include <cassert>

/* 
 * Classic rectangle example of LSP violation.
 * It’s probably best not to inherit at all in this case.
 */

class Rectangle {
    int height;
    int width;

public:
    explicit Rectangle(const int height, const int width)
        : height{height}, width{width} {}

    void setHeight(const int value) { 
        height = value;
    }

    void setWidth(const int value) { 
        width = value; 
    }

    int getArea() const {
        return height * width;
    }
};

class Square {
    int side;
public:
    explicit Square(const int side): side{side} {}

    void setSide(const int value) { 
        side = value;
    }

    int getArea() const {
        return side * side;
    }
};

int changeArea(Rectangle & rec) {
    assert(rec.getArea() != 0);
    rec.setHeight(4);
    rec.setWidth(5);
    assert(rec.getArea() == 20);
    return rec.getArea();
}

int changeArea(Square & rec) {
    assert(rec.getArea() != 0);
    rec.setSide(4);
    assert(rec.getArea() == 16);
    return rec.getArea();
}

int main() {
    Rectangle rectangle{1, 3};
    Square square{2};
    changeArea(rectangle);
    changeArea(square);
}
