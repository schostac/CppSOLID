#include <iostream>
#include <cassert>

/* Classic rectangle example of LSP violation */

class Rectangle {
protected:
    int height;
    int width;

public:
    explicit Rectangle(const int height, const int width)
    : height{height}, width{width} {
        assert(getArea() != 0);
    }

    virtual ~Rectangle() = default;

    virtual void setHeight(const int value) { 
        height = value;
    }

    virtual void setWidth(const int value) { 
        width = value; 
    }

    virtual int getArea() const {
        return height * width;
    }
};

class Square: public Rectangle {
public:
    explicit Square(const int side): Rectangle(side, side) {
        assert(getArea() != 0);
    }

    void setHeight(const int value) override {
        setSide(value);
    }

    void setWidth(const int value) override {
        setSide(value);
    }

    void setSide(const int value) { 
        height = value;
        width = value;
    }
};

int changeArea(Rectangle & rec) {
    assert(rec.getArea() != 0);
    rec.setHeight(4);
    rec.setWidth(5);
    assert(rec.getArea() == 20);
    return rec.getArea();
}

int main() {
    Rectangle rectangle{1, 3};
    Square square{2};
    changeArea(rectangle);
    changeArea(square);
}
