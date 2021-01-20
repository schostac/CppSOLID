#include <iostream>

/* Classic lamp example of DIP.
 * In this case DIP is followed by using static polymorphism and templates.
 */

// This is our explicit abstraction
// but could also be implicit (similar to duck typing)
template <typename T> concept Switchable = requires(T t)
{
    t.switchOn();
    t.switchOff();
};

// Client module, policy, higher layer
template <typename Switchable> class Button {
    Switchable& switchable;
    bool on = false;

public:
    Button(Switchable& switchable)
        : switchable{ switchable }
    {
    }
    void toggle()
    {
        if (on)
            switchable.switchOff();
        else
            switchable.switchOn();
        on = !on;
    }
};

// Service module, implementation detail, lower layer
class Lamp1 {
public:
    void switchOn() { std::cout << "Lamp1 is on" << std::endl; };
    void switchOff() { std::cout << "Lamp1 is off" << std::endl; }
};

class Lamp2 {
public:
    void switchOn() { std::cout << "Lamp2 is on" << std::endl; };
    void switchOff() { std::cout << "Lamp2 is off" << std::endl; }
};

int main()
{
    Lamp1 lamp1;
    Button<Lamp1> button1(lamp1);
    button1.toggle();
    button1.toggle();

    Lamp2 lamp2;
    Button<Lamp2> button2(lamp2);
    button2.toggle();
    button2.toggle();

    return 0;
}