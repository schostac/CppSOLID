#include <iostream>
#include <stdexcept>
#include <optional>
#include <memory>

/* Classic door example of ISP.
 * See more in article by Robert C. Martin,
 * The Interface Segregation Principle, C++ Report, June 1996,
 * or his book Agile Principles, Patterns, and Practices in C#.
 * 
 * Here we use multiple inheritance to follow ISP.
 */

class TimerClient {
public:
    virtual ~TimerClient() = default;
    virtual void timeout() = 0;
};

class Door {
public:
    virtual ~Door() = default;
    virtual void open() = 0;
    virtual void close() = 0;
};

class Timer {
    TimerClient& client;
public:
    Timer(TimerClient& client): client{client} {
        // Call immediately in constructor, in reality it'd be after some time in other place
        client.timeout();
    }
};

class TimedDoor : public Door, public TimerClient {
    std::optional<Timer> timer;
public:
    void open() override { 
        std::cout << "Open" << std::endl;
        timer.emplace(Timer(*this));
    }
    void close() override { 
        std::cout << "Close" << std::endl;
    }
    void timeout() {
        std::cout << "Timeout" << std::endl;
        close();
        timer = std::nullopt;
    }
};

class NormalDoor : public Door {
public:
    void open() override { 
        std::cout << "Open" << std::endl;
    }
    void close() override { 
        std::cout << "Close" << std::endl;
    }
};

int main()
{
    TimedDoor door;
    door.open();
    door.open();

    return 0;
}