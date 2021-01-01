#include <cassert>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <map>
#include <mutex>
#include <optional>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>
#include <set>

std::mutex sensorsMutex;

class AbstractPlantCareTaker {
public:
    virtual ~AbstractPlantCareTaker() = default;

    virtual void pourWater() = 0;
    virtual void sprinkleWater() = 0;

    virtual void openWindowBlinds() = 0;
    virtual void closeWindowBlinds() = 0;
};

class SunlightSensor {
    using TimePoint = decltype(std::chrono::system_clock::now());

    const std::chrono::seconds sleepTime;
    std::set<AbstractPlantCareTaker*> plantCareTakers;

    std::optional<TimePoint> sunlightOnFrom;
    std::optional<TimePoint> sunlightOffFrom;

    const int threshold = 3;
    bool sensorOn = true;

public:
    SunlightSensor(const std::chrono::seconds sleepTime)
        : sleepTime{ sleepTime }
    {
    }

    void subscribe(AbstractPlantCareTaker& plantCareTaker) {
        plantCareTakers.insert(&plantCareTaker);
    }

    void operator()()
    {
        for (;;) {
            const auto sunlight = isSunlight();
            updateState(sunlight);

            std::unique_lock<std::mutex> lock(sensorsMutex);
            std::cout << "Sun on: " << std::boolalpha << sunlight << std::endl;

            if (isTooMuchSunlight(sunlight)) {
                for (auto p : plantCareTakers)
                    p->closeWindowBlinds();
                sensorOn = false;
            } else if (isTooLittleSunlight(sunlight)) {
                for (auto p : plantCareTakers)
                    p->openWindowBlinds();
                sensorOn = true;
            }

            lock.unlock();
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

    void updateState(const bool sunlight)
    {
        const auto currentTime = std::chrono::system_clock::now();
        if (sunlight and sensorOn) {
            sunlightOnFrom = sunlightOnFrom ? *sunlightOnFrom : currentTime;
            sunlightOffFrom = std::nullopt;
        } else if (not sunlight) {
            sunlightOffFrom = sunlightOffFrom ? *sunlightOffFrom : currentTime;
            sunlightOnFrom = std::nullopt;
        }
    }

    bool isSunlight() const
    {
        static bool sunOn = true;
        static std::mt19937 generator;
        auto prob = std::uniform_int_distribution<int>(1, 100)(generator);
        if (prob >= 90)
            sunOn = !sunOn;
        return sunOn;
    }
};

class MoistureSensor {
    const std::chrono::seconds sleepTime;
    std::set<AbstractPlantCareTaker*> plantCareTakers;

    const int min = 0;
    const int max = 10;
    const int threshold = 5;

public:
    MoistureSensor(const std::chrono::seconds sleepTime)
        : sleepTime{ sleepTime }
    {
    }

    void subscribe(AbstractPlantCareTaker& plantCareTaker) {
        plantCareTakers.insert(&plantCareTaker);
    }

    void operator()()
    {
        for (;;) {
            std::unique_lock<std::mutex> lock(sensorsMutex);

            if (isAirTooDry())
                for (auto p : plantCareTakers)
                    p->sprinkleWater();
            if (isSoilTooDry())
                for (auto p : plantCareTakers)
                    p->pourWater();

            lock.unlock();
            std::this_thread::sleep_for(sleepTime);
        }
    }

    bool isAirTooDry() { return getAirMoisture() < threshold; }

    bool isSoilTooDry() { return getSoilMoisture() < threshold; }

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

class AloeCareTaker : public AbstractPlantCareTaker {
    bool windowBlindsOpen = true;
public:
    void pourWater() override { std::cout << "Pouring water" << std::endl; }

    void sprinkleWater() override { std::cout << "Sprinkling water" << std::endl; }

    void openWindowBlinds() override {
        if (not windowBlindsOpen) {
            windowBlindsOpen = true;
            std::cout << "Opened window blinds" << std::endl;
        }
    }

    void closeWindowBlinds() override {
        if (windowBlindsOpen) {
            windowBlindsOpen = false;
            std::cout << "Closed window blinds" << std::endl;
        }
    }
};

void run() {
    auto sunlightSensor = SunlightSensor(std::chrono::seconds(1));
    auto moistureSensor = MoistureSensor(std::chrono::seconds(3));

    AloeCareTaker aloeCareTaker;
    sunlightSensor.subscribe(aloeCareTaker);
    moistureSensor.subscribe(aloeCareTaker);

    std::thread sunlightSensorThread(sunlightSensor);
    std::thread moistureSensorThread(moistureSensor);

    sunlightSensorThread.join();
    moistureSensorThread.join();
}

int main()
{
    run();
    return 0;
}