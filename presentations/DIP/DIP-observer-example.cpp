#include <iostream>
#include <set>

/* Observer pattern example of DIP.
 * DIP is violated because we depend on concrete implementations. 
 * Note that we also have circular dependency.
 */

class WheatherForecast;

class User {
public:
    User(WheatherForecast&);
    void notify();
};

class WheatherForecast {
    std::set<User*> listeners;

public:
    void subscribe(User&);
    void update();
};

User::User(WheatherForecast& forecast) { forecast.subscribe(*this); }
void User::notify() { std::cout << "Notified " << this << std::endl; }

void WheatherForecast::subscribe(User& user) { listeners.insert(&user); }
void WheatherForecast::update()
{
    for (auto& l : listeners) {
        l->notify();
    }
}

int main()
{
    WheatherForecast forecast;
    User user1(forecast), user2(forecast);
    forecast.update();

    return 0;
}