#include <iostream>
#include <memory>


/* Inheritance is not always a good choice.
 * Sometimes it’s preferred to use composition over inheritance,
 * which can also conform to OCP.
 * 
 * As it’s sometimes said, we do not have polymorphic types,
 * we have polymorphic use of types.
 *
 * Some links related to the topic
 * https://en.wikipedia.org/wiki/Composition_over_inheritance
 * https://stackoverflow.com/questions/406081/why-should-i-avoid-multiple-inheritance-in-c 
 * https://softwareengineering.stackexchange.com/questions/134097/why-should-i-prefer-composition-over-inheritance 
 * https://softwareengineering.stackexchange.com/questions/218458/is-there-any-real-reason-multiple-inheritance-is-hated 
 * https://stackoverflow.com/questions/49002/prefer-composition-over-inheritance
 */


class SwimDelegate {
public:
    virtual ~SwimDelegate() = default;
    virtual void swim() const = 0;
};

class Submarine : public SwimDelegate {
public:
    void swim() const override {
        std::cout << "Submarine moving" << std::endl;
    };
};

class AircraftCarrier : public SwimDelegate {
public:
    void swim() const override {
        std::cout << "Aircraft carrier moving" << std::endl;
    };
};


class FlyDelegate {
public:
    virtual ~FlyDelegate() = default;
    virtual void fly() const = 0;
};

class Helicopter : public FlyDelegate {
public:
    void fly() const override {
        std::cout << "Helicopter moving" << std::endl;
    };
};

class FighterAircraft : public FlyDelegate {
public:
    void fly() const override {
        std::cout << "Fighter aircraft moving" << std::endl;
    };
};


// We compose Player by what it can do (HAS-A relashionship)
// rather then extend what it is (IS-A relashionship)
class Player {
    std::unique_ptr<SwimDelegate> _swimDelegate;
    std::unique_ptr<FlyDelegate> _flyDelegate;
public:
    Player(std::unique_ptr<SwimDelegate> swimDelegate,
           std::unique_ptr<FlyDelegate> flyDelegate)
    : _swimDelegate{std::move(swimDelegate)},
      _flyDelegate{std::move(flyDelegate)}
    {}

    void swim() { if (_swimDelegate) _swimDelegate->swim(); }
    void fly() { if (_flyDelegate) _flyDelegate->fly(); }
};


int main() {
    Player player1(std::make_unique<Submarine>(), std::make_unique<Helicopter>());
    player1.swim();
    player1.fly();

    Player player2(std::make_unique<AircraftCarrier>(), std::make_unique<FighterAircraft>());
    player2.swim();
    player2.fly();
}
