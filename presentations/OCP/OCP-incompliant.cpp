#include <iostream>

/* OCP incompliant example */

// Service code
class Dog {
public:
    void bark() const {
        std::cout << "Bark...\n";
    }
};

class Cat {
public:
    void meo() const {
        std::cout << "Meow...\n";
    }
};

// Client code
void speak(const Dog & dog) {
    std::cout << "Hello\n";
    dog.bark();
}

void speak(const Cat & cat) {
    std::cout << "Hello\n";
    cat.meo();
}

int main() {
    Dog dog;
    Cat cat;
    speak(dog);
    speak(cat);
}
