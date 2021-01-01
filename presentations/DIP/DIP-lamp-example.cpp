#include <iostream>

/* Classic lamp example of DIP.
 * In this case DIP is violated as we depend on concrete implementation.
 * Idea for the example is from Robert C. Martin's book
 * Agile Principles, Patterns, and Practices in C#.
 */

// Implementation detail, lower layer
class Lamp {
public:
    void switchOn() { std::cout << "Lamp is on" << std::endl; };
    void switchOff() { std::cout << "Lamp is off" << std::endl; };
};

// Policy, higher layer
class Button {
    Lamp& lamp;
    bool on = false;

public:
    Button(Lamp& lamp)
        : lamp{ lamp }
    {
    }
    void toggle()
    {
        if (on)
            lamp.switchOff();
        else
            lamp.switchOn();
        on = !on;
    }
};

int main()
{
    Lamp lamp;
    Button button(lamp);
    button.toggle();
    button.toggle();

    // But what if we have other types of lamps?

    return 0;
}