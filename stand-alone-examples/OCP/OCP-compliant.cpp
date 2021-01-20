#include <iostream>

/* OCP compliant example.
 * The most basic solution is to depend on an abstraction,
 * use polymorphism and inheritance.
 */


// Service code
class Animal {
public:
    virtual ~Animal() = default;
    virtual void speak() const = 0;
};

class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Bark...\n";
    }
};

class Cat : public Animal {
public:
    void speak() const override {
        std::cout << "Meow...\n";
    }
};

// Client code
void speak(const Animal & animal) {
    std::cout << "Hello\n";
    animal.speak();
}

int main() {
    Dog dog;
    Cat cat;
    speak(dog);
    speak(cat);
}
