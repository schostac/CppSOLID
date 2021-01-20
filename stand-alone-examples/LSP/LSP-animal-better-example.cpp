#include <iostream>
#include <stdexcept>

/*  Continuation of animal example where LSP is violated. Here it's not.
 *  We have extracted separate super-classes with methods specific only to some sub-classes. 
 *  
 *  Note that if Flyable and Walkable were independent, then Eagle class would have to inherit
 *  from both; this would lead to problems as we have function overloads for both Flyable
 *  and Walkable, which creates ambiguity.
 * 
 *  Note also that if Walkable and Flyable both inherited from Animal directly,
 *  then in case of Eagle we would have to use virtual inheritance (diamond problem).
 * 
 *  So try to avoid multiple inheritance when possible.
 */

class Animal {
public:
    virtual ~Animal() = default;
    virtual void move() = 0;
    virtual void speak() = 0;
};

class Walkable : public Animal {
public:
    virtual void walk() = 0;
};

class Flyable : public Walkable {
public:
    virtual void fly() = 0;
};

class Eagle : public Flyable {
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
    void move() override {
        fly(); // Let's say that by default eagles move by flying
    }
};

class Dog : public Walkable  {
public:
    void speak() override {
        std::cout << "Dog speaking" << std::endl;
    }
    void walk() override {
        std::cout << "Dog walking" << std::endl;
    }
    void move() override {
        walk();
    }
};

void foo(Animal & animal) {
    animal.move();
    animal.speak();
}

void bar(Flyable & flyable) {
    flyable.fly();
}

void bar(Walkable & walkable) {
    walkable.walk();
}

int main() {
    Eagle eagle;
    Dog dog;

    foo(eagle);
    bar(eagle);
    foo(dog);
    bar(dog);
}
