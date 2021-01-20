#include <iostream>
#include <stdexcept>

/*  Animal example of LSP violation.
 *  Super-class has methods specific only to some sub-classes.
 *  And empty classes in the middle are probably redundant.
 */

class Animal {
public:
    virtual ~Animal() = default;
    virtual void speak() = 0;
    virtual void walk() = 0;
    virtual void fly() = 0;
};

class Bird: public Animal {};
class Mammal: public Animal {};

class Eagle : public Bird {
public:
    void speak() override {
        std::cout << "Eagle speaking" << std::endl;
    }
    void walk() override {
        std::cout << "Eagle walking" << std::endl;
    }
    void fly() override {
        std::cout << "Eagle flying" << std::endl;
    }
};

class Dog : public Mammal {
public:
    void speak() override {
        std::cout << "Dog speaking" << std::endl;
    }
    void walk() override {
        std::cout << "Dog walking" << std::endl;
    }
    void fly() override {
        throw std::logic_error("Not implemented");
    }
};

void foo(Animal & animal) {
    animal.fly();
}

void bar(Animal & animal) {
    if(Bird* bird = dynamic_cast<Bird*>(&animal)) {
        bird->fly();
    }
}

int main() try {
    Eagle eagle;
    Dog dog;

    foo(eagle);
    bar(eagle);
    bar(dog);
    foo(dog);

} catch(const std::exception &e) {
    std::cout << e.what() << std::endl;
}
