#include <iostream>
#include <set>

/* Observer pattern example of DIP.
 * DIP is followed because we depend on abstractions instead of concrete implementations.
 * In this case we use dynamic polymorphism (virtual functions and inheritance).
 * Note that we also have circular dependency. It'd be better to extract subscription
 * from constructor of User, and thus dependency on Forecast.
 */

class Subscriber;

class Forecast {
public:
    virtual ~Forecast() = default;
    virtual void subscribe(Subscriber&) = 0;
};

class Subscriber {
public:
    virtual ~Subscriber() = default;
    virtual void notify() = 0;
};

class WheatherForecast : public Forecast {
    std::set<Subscriber*> subscribers;

public:
    void subscribe(Subscriber& subscriber) override { subscribers.insert(&subscriber); }
    void update()
    {
        for (auto& s : subscribers) {
            s->notify();
        }
    }
};

class User : public Subscriber {
public:
    User(Forecast& forecast) { forecast.subscribe(*this); }
    void notify() { std::cout << "Notified " << this << std::endl; }
};

int main()
{
    WheatherForecast forecast;
    User user1(forecast), user2(forecast);
    forecast.update();

    return 0;
}