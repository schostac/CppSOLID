#include <iostream>
#include <stdexcept>

/* Printer example of ISP
 * Users depend on some methods of device interface
 * that they do not need.
 */

// Interfaces
class Device {
public:
    virtual ~Device() = default;
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;
};

// Implementation
class AdvancedPrinter : public Device {
public:
    void print() override {
        std::cout << "Printing" << std::endl;
    }
    void scan() override {
        std::cout << "Scaning" << std::endl;
    }
    void fax() override {
        std::cout << "Faxing" << std::endl;
    }
};

class SimplePrinter : public Device {
public:
    void print() override {
        std::cout << "Printing" << std::endl;
    }
    void scan() override {
        throw std::runtime_error{"Not implemented"};
    }
    void fax() override {
        throw std::runtime_error{"Not implemented"};
    }
};

// Clients
void printUser(Device & device) {
    device.print();
}

void scanUser(Device & device) {
    device.scan();
}

void faxUser(Device & device) {
    device.fax();
}

int main()
{
    AdvancedPrinter advancedPrinter;
    SimplePrinter simplePrinter;

    printUser(simplePrinter);
    scanUser(advancedPrinter);
    faxUser(advancedPrinter);
    scanUser(simplePrinter); // oops

    return 0;
}