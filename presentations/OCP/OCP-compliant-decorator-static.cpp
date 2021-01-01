#include <iostream>
#include <memory>
#include <cassert>

/* We can also use decorator pattern to help us conform to OCP.
 * The following is an example of static decorator (dynamic one is in the previous example).
 * Note C++20's concepts (remove if you want to compile in previous versions).
 */

class Dog {
    std::string m_name;
public:
    Dog(std::string name):m_name{std::move(name)} {}
    void speak() const {
        std::cout << m_name << " barking...\n";
    }
};

class Cat {
    std::string m_name;
public:
    Cat(std::string name):m_name{std::move(name)} {}
    void speak() const {
        std::cout << m_name << " meowing...\n";
    }
};

template <typename T>
concept Speakable = requires(T t) {
    t.speak();
};

// Extend the speak behaviour of any class that has speak method
template<Speakable T>
class SpeakableDecorator: public T {
public:
    template <typename ...Args>
    SpeakableDecorator(Args&&... args): T(std::forward<Args>(args)...) {}

    void speak() const {
        std::cout << "Decorated: ";
        T::speak();
    }
};

template<Speakable Animal>
void speak(const Animal & animal) {
    std::cout << "Hello\n";
    animal.speak();
}

int main() {
    auto decoratedDog = SpeakableDecorator<Dog>("Charlie");
    auto decoratedCat = SpeakableDecorator<Cat>("Tom");

    speak(decoratedDog);
    speak(decoratedCat);
}
