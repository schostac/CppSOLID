#include <iostream>
#include <stdexcept>

/* Printer example of ISP
 * Here users do not depend any methods that they do not need.
 * Each user depends on its own interface.
 * Of course, it’s a bit extreme example, but the idea is clear. 
 */

// Interfaces
class Printer {
public:
    virtual ~Printer() = default;
    virtual void print() = 0;
};

class Scanner {
public:
    virtual ~Scanner() = default;
    virtual void scan() = 0;
};

class Fax {
public:
    virtual ~Fax() = default;
    virtual void fax() = 0;
};

// Implementation
class AdvancedPrinter : public Printer, public Scanner, public Fax {
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

class SimplePrinter : public Printer {
public:
    void print() override {
        std::cout << "Printing" << std::endl;
    }
};

// Clients
void printUser(Printer & printer) {
    printer.print();
}

void scanUser(Scanner & scanner) {
    scanner.scan();
}

void faxUser(Fax & fax) {
    fax.fax();
}

int main()
{
    AdvancedPrinter advancedPrinter;
    SimplePrinter simplePrinter;

    printUser(simplePrinter);
    scanUser(advancedPrinter);
    faxUser(advancedPrinter);
    // scanUser(simplePrinter); // Won't compile

    return 0;
}