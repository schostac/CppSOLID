#pragma once

#include <chrono>
#include <mutex>
#include <set>

#include "caretaker/WaterDevice.hpp"

namespace sensors {
class MoistureSensor {
    const std::chrono::seconds sleepTime;
    std::mutex& mtx;
    std::set<interfaces::WaterDevice*> devices;

    const int min = 0;
    const int max = 10;
    const int threshold = 3;

public:
    MoistureSensor(const std::chrono::seconds, std::mutex& mtx);
    void subscribe(interfaces::WaterDevice&);
    void operator()();

private:
    bool isAirTooDry();
    bool isSoilTooDry();
    int getAirMoisture();
    int getSoilMoisture();
};
} // namespace sensors