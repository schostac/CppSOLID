#include <iostream>
#include <memory>

class A {
public:
    virtual ~A() = default;
    virtual void foo() { std::cout << "A" << std::endl; }
};

class B : public virtual A {
public:
    void foo() override { std::cout << "B" << std::endl; }
};

class C : public virtual A {
public:
    void foo() override { std::cout << "C" << std::endl; }
};

class D : public B, public C  {
public:
    void foo() override { std::cout << "D" << std::endl; } // Otherwise no unique overrider
};

/*
/\
\/
*/

int main()
{
    std::unique_ptr<A> p = std::make_unique<D>();
    p->foo();
    return 0;
}
