#include <iostream>
#include <stdexcept>
#include <optional>
#include <memory>

/* Classic door example of ISP.
 * See more in article by Robert C. Martin,
 * The Interface Segregation Principle, C++ Report, June 1996,
 * or his book Agile Principles, Patterns, and Practices in C#.
 * 
 * Here we use adapter pattern to follow ISP.
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

class TimedDoorAdapter;

class TimedDoor : public Door {
    std::unique_ptr<TimedDoorAdapter> adapter;
public:
    void open() override { 
        std::cout << "Open" << std::endl;
        adapter = std::make_unique<TimedDoorAdapter>(*this);
    }
    void close() override { 
        std::cout << "Close" << std::endl;
    }
    void timeout() {
        std::cout << "Timeout" << std::endl;
        close();
        adapter = nullptr;
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

class TimedDoorAdapter : public TimerClient {
    TimedDoor & door;
    Timer timer;
public:
    TimedDoorAdapter(TimedDoor& door): door{door}, timer{Timer(*this)} {}
    void timeout() override { door.timeout(); }
};

int main()
{
    TimedDoor door;
    door.open();
    door.open();

    return 0;
}