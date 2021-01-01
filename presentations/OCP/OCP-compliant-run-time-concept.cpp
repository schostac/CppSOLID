#include <iostream>
#include <memory>
#include <cassert>
#include <vector>

/*
 * The run-time concept idiom can be useful for OCP.
 * It allows unmodified concrete types to behave in run-time polymorphic manner
 * It erases types using templates and dynamic polymorphism and has 3 layers:
 * wrapper, concept, model. For example, std::function and std::any use similar approach.
 * 
 * We may depend on a wrapper type, which can take and wrap any types that confirm
 * to some interface (something like compile time concepts in C++20). 
 * 
 * The following is a simple example of that.
 * For more information, you may check these out:
 * https://stackoverflow.com/questions/26185268/what-are-c-run-time-concepts
 * https://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil
 * https://www.stroustrup.com/oops08.pdf  
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

class Wrapper {
public:
    template <Speakable T>
    Wrapper(T&& speakable):
        ptr{std::make_unique<Model<T>>(std::forward<T>(speakable))} {}
    void speak() const { ptr->speak(); }
private:
    class Concept {
    public:
        virtual ~Concept() = default;
        virtual void speak() const = 0;
    };

    template<Speakable T>
    class Model : public Concept {
    public:
        Model(T && speakable):
            m_speakable{std::move(speakable)}{}
        void speak() const override {
            std::cout << "Logic extended: ";
            m_speakable.speak();
        }
    private:
        T m_speakable;
    };
    
    std::unique_ptr<Concept> ptr;
};


// Client code
void talk(const std::vector<Wrapper>& vec) {
    for(const auto & e : vec) {
        std::cout << "Hello. ";
        e.speak();
    }
}

int main() {
    std::vector<Wrapper> vec;

    // We can now push to vector an instance of any Speakable type - 
    // class that has speak method.
    // We do not need to inherit from such types but we can extend the logic
    // inside the wrapper without modifying those types or the talk function above.
    vec.emplace_back(Wrapper(Dog("Buddy")));
    vec.emplace_back(Wrapper(Cat("Tom")));

    talk(vec);

    return 0;
}
