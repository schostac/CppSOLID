#include <iostream>
#include <set>

/* Observer pattern example of DIP.
 * DIP is followed because we depend on abstractions instead of concrete implementations.
 * In this case we use static polymorphism and templates.
 * Note that we also have broken circular dependency.
 */

template <typename T> concept Notifyable = requires(T t)
{
    t.notify();
};

template<Notifyable T>
class WheatherForecast {
    std::set<T*> subscribers;

public:
    void subscribe(T& subscriber) { subscribers.insert(&subscriber); }
    void update()
    {
        for (auto& s : subscribers) {
            s->notify();
        }
    }
};

class User {
public:
    void notify() { std::cout << "Notified " << this << std::endl; }
};

int main()
{
    WheatherForecast<User> forecast;
    User user1, user2;
    forecast.subscribe(user1);
    forecast.subscribe(user2);
    forecast.update();

    return 0;
}