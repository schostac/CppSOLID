#include <iostream>
#include <memory>
#include <cassert>
#include <vector>

/* We can also use decorator pattern to help us conform to OCP.
 * It allows to added behavior to an individual object without
 * affecting the behavior of other objects from the same class.
 * The following is an example of dynamic decorator.
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

// Extend the speak behaviour of any object of any Animal subclass without
// inheriting from such subclass or changing such subclass. In other words,
// here we don't inherit from Cat and Dog (just Animal interface) but add additional
// functionality to the object.
// We may also further create subclasses that inherit from AnimalDecorator.
class AnimalDecorator: public Animal {
    std::unique_ptr<Animal> m_animal;
public:
    AnimalDecorator(std::unique_ptr<Animal> animal)
    : m_animal{std::move(animal)} {
        assert(m_animal != nullptr);
    }
    
    void speak() const override {
        std::cout << "Decorated: ";
        m_animal->speak();
    }
};


// Client code
void speak(const Animal & animal) {
    std::cout << "Hello\n";
    animal.speak();
}

int main() {
    std::vector<std::unique_ptr<Animal>> animals;

    animals.emplace_back(std::make_unique<AnimalDecorator>((std::make_unique<Dog>())));
    animals.emplace_back(std::make_unique<Cat>());

    for (auto & animal : animals) {
        speak(*animal);
    }
}
