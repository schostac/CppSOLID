#include <iostream>

/* In C++20 we can also use concepts to make the expected
 * interface more explicit, improve readability and debugging. 
 */

template <typename T>
concept Flyable = requires(T t) {
    t.fly();
};

template <typename T>
concept Swimable = requires(T t) {
    t.swim();
};


template<Flyable T>
void action(const T & t) {
    std::cout << "Let's fly\n";
    t.fly();
}

template<Swimable T>
void action(const T & t) {
    std::cout << "Let's swim\n";
    t.swim();
}


class Bird {
public:
    void fly() const {
        std::cout << "Fly...\n";
    }
};

class Fish {
public:
    void swim() const {
        std::cout << "Swim...\n";
    }
};


int main() {
    Bird bird;
    Fish fish;
    action(bird);
    action(fish);
}
