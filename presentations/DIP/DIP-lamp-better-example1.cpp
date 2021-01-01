#include <iostream>

/* Classic lamp example of DIP.
 * In this case DIP is followed by using dynamic polymorphism.
 */

// This is our explicit abstraction
class Switchable {
public:
    virtual ~Switchable() = default;
    virtual void switchOn() = 0;
    virtual void switchOff() = 0;
};

// Client module, policy, higher layer
class Button {
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
class Lamp1 : public Switchable {
public:
    void switchOn() override { std::cout << "Lamp1 is on" << std::endl; };
    void switchOff() override { std::cout << "Lamp1 is off" << std::endl; }
};

class Lamp2 : public Switchable {
public:
    void switchOn() override { std::cout << "Lamp2 is on" << std::endl; };
    void switchOff() override { std::cout << "Lamp2 is off" << std::endl; }
};

int main()
{
    Lamp1 lamp1;
    Button button1(lamp1);
    button1.toggle();
    button1.toggle();

    Lamp2 lamp2;
    Button button2(lamp2);
    button2.toggle();
    button2.toggle();

    return 0;
}