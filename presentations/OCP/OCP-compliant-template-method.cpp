#include <iostream>
#include <memory>
#include <cassert>

/* Template method pattern allows derivative classes to extend and/or modify
 * the basic behavior defined in the base classes.
 */

class Base {
public:
    // Template method that a client calls, it defines the skeleton of some behaviour,
    // and expects certain methods to be implemented by subclasses, note no virtual
    void method() {
        this->stepA();
        this->stepB();
        this->setpC(); 
    }
protected:
    // Required to be implemented, note purely virutal function 
    virtual void stepA() = 0; 

    // Hook method - has default logic but subclasses may override it
    virtual void stepB() {
        std::cout << "Step B. Hook method" << std::endl;
    }

    // Already implemented, note no virtual
    void setpC() {
        std::cout << "Step C. Invariant method" << std::endl;
    }
};

class Subclass1 : public Base {
protected:
    void stepA() override {
        std::cout << "Step A. Subclass1's method" << std::endl;
    } 
};

class Subclass2 : public Base {
protected:
    void stepA() override {
        std::cout << "Step A. Subclass2's method" << std::endl;
    }

    void stepB() override {
        std::cout << "Step B. Hook method overridden" << std::endl;
    }
};

int main() {
    std::unique_ptr<Base> b1 = std::make_unique<Subclass1>();
    std::unique_ptr<Base> b2 = std::make_unique<Subclass2>();

    b1->method();
    
    std::cout << std::endl;

    b2->method();
}
