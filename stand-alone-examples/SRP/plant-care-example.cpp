#include <cassert>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <optional>
#include <random>
#include <thread>
#include <stdexcept>
#include <string>
#include <set>

/* Example where SRP is violated.
 * This code modeles some smart device that takes care of home plants.
 * Here some other SOLID principles are also violated
 * but we will discuss those in other sections.
 */


/* This class represents the part of the device that can pour or sprinkle water to moisturize soil
 * or air if it’s too dry, close or open window blinds if there is too much or too little sunlight.
 * Sensors detect such changes in conditions and talk to this class through its interface (methods).  
 */
class PlantCaretaker {
    bool windowBlindsOpen = true;
public:
    void pourWater() { std::cout << "Pouring water" << std::endl; }

    void sprinkleWater() { std::cout << "Sprinkling water" << std::endl; }

    void openWindowBlinds() {
        if (not windowBlindsOpen) {
            windowBlindsOpen = true;
            std::cout << "Opened window blinds" << std::endl;
        }
    }

    void closeWindowBlinds() {
        if (windowBlindsOpen) {
            windowBlindsOpen = false;
            std::cout << "Closed window blinds" << std::endl;
        }
    }
};

/* This class detects changes in conditions such as
 * (a) air and soil moisture and
 * (b) amount of sunlight.
 * Then it informs the subscribed caretakers about certain changes in conditions
 * so that they could react to the changes. 
 * However, note the following:
 * - This class is responsible for detecting unrelated (incohesive) changes – moisture and sunlight,
 * - The main loop with sleeps is big and does too much.
 * - What if certain subscribers are interested only in moisture or sunlight changes but not both?
 * - What if later we want to monitor some other unrelated conditions?
 * - What if sleep-time should be different for checking moisture and sunlight?
 */
class Sensor {
    using TimePoint = decltype(std::chrono::system_clock::now());

    const std::chrono::seconds sleepTime;
    std::set<PlantCaretaker*> plantCaretakers;

    std::optional<TimePoint> sunlightOnFrom;
    std::optional<TimePoint> sunlightOffFrom;

    bool sensorOn = true;
    const int min = 0;
    const int max = 10;
    const int threshold = 3;

public:
    Sensor(const std::chrono::seconds sleepTime)
        : sleepTime{ sleepTime }
    {
    }

    void subscribe(PlantCaretaker& plantCaretaker) {
        plantCaretakers.insert(&plantCaretaker);
    }

    void operator()()
    {
        for (;;) {
            const auto sunlight = isSunlight();
            std::cout << "Sun on: " << std::boolalpha << sunlight << std::endl;

            if (isTooMuchSunlight(sunlight)) {
                for (auto p : plantCaretakers)
                    p->closeWindowBlinds();
                sensorOn = false;
            } else if (isTooLittleSunlight(sunlight)) {
                for (auto p : plantCaretakers)
                    p->openWindowBlinds();
                sensorOn = true;
            }

            if (isAirTooDry()) {
                for (auto p : plantCaretakers)
                    p->sprinkleWater();
            }
            if (isSoilTooDry()) {
                for (auto p : plantCaretakers)
                    p->pourWater();
            }

            std::this_thread::sleep_for(sleepTime);
        }
    }

    bool isTooMuchSunlight(const bool sunlight)
    {
        if (sunlight) {
            auto timeNow = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsedSeconds = timeNow - (*sunlightOnFrom);
            return elapsedSeconds.count() > threshold;
        }
        return false;
    }

    bool isTooLittleSunlight(const bool sunlight)
    {
        if (not sunlight) {
            auto timeNow = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsedSeconds = timeNow - (*sunlightOffFrom);
            return elapsedSeconds.count() > threshold;
        }
        return false;
    }

    bool isSunlight()
    {
        /* We simulate changes of sunlight by generating random numbers that represent
         * a probability of change in sunlight conditions: if the sun shines or not.
         */
        static bool sunlightOn = true;
        static std::mt19937 generator;

        auto prob = std::uniform_int_distribution<int>(1, 100)(generator);
        if (prob >= 90) {
            sunlightOn = !sunlightOn;
        }

        const auto currentTime = std::chrono::system_clock::now();
        if (sunlightOn and sensorOn) {
            sunlightOnFrom = sunlightOnFrom ? *sunlightOnFrom : currentTime;
            sunlightOffFrom = std::nullopt;
        } else if (not sunlightOn) {
            sunlightOffFrom = sunlightOffFrom ? *sunlightOffFrom : currentTime;
            sunlightOnFrom = std::nullopt;
        }

        return sunlightOn;
    }

    bool isAirTooDry() { return getAirMoisture() < threshold; }

    bool isSoilTooDry() { return getSoilMoisture() < threshold; }

    /* We simulate changes of moisture by generating random numbers that
     * represent the degree to which something is moisturized,
     * and then we use the threshold for sensors to trigger.
     */
    int getAirMoisture()
    {
        static std::mt19937 generator;
        return std::uniform_int_distribution<int>(min, max)(generator);
    }

    int getSoilMoisture()
    {
        static std::mt19937 generator;
        return std::uniform_int_distribution<int>(min, max)(generator);
    }
};

void run() {
    auto sensor = Sensor(std::chrono::seconds(1));

    PlantCaretaker plantCaretaker;
    sensor.subscribe(plantCaretaker);
    
    sensor();
}

int main()
{
    run();
    return 0;
}