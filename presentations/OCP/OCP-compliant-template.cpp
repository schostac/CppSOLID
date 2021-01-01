#include <iostream>

/* In C++ we can also use templates to close certain parts of code
 * for some expected modifications when functionality is extended
 * and help us stick to OCP.
 * In this context the following Q&A is also interesting:
 * https://stackoverflow.com/a/43577925/9497808
 */

// Service code
class Dog {
public:
    void speak() const {
        std::cout << "Bark...\n";
    }
};

class Cat {
public:
    void speak() const {
        std::cout << "Meow...\n";
    }
};


// Client code
template<typename Animal>
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
