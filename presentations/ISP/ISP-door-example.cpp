#include <iostream>
#include <stdexcept>
#include <optional>

/* Classic door example of ISP.
 * See more in article by Robert C. Martin,
 * The Interface Segregation Principle, C++ Report, June 1996,
 * or his book Agile Principles, Patterns, and Practices in C#.
 */

class TimerClient {
public:
    virtual ~TimerClient() = default;
    virtual void timeout() = 0;
};

class Door : public TimerClient {
public:
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

class TimedDoor : public Door {
    std::optional<Timer> timer;
public:
    void open() override { 
        std::cout << "Open" << std::endl;
        timer.emplace(Timer(*this));
    }
    void close() override { 
        std::cout << "Close" << std::endl;
    }
    void timeout() override {
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
    void timeout() override {
        throw std::runtime_error{"Not implemented"};
    }
};

int main()
{
    TimedDoor door1;
    door1.open();
    door1.open();

    NormalDoor door2;

    return 0;
}