#pragma once

#include <chrono>
#include <mutex>
#include <set>

#include "caretaker/AbstractPlantCaretaker.hpp"

namespace sensors {
class MoistureSensor {
    const std::chrono::seconds sleepTime;
    std::mutex& mtx;
    std::set<interfaces::AbstractPlantCaretaker*> caretakers;

    const int min = 0;
    const int max = 10;
    const int threshold = 3;

public:
    MoistureSensor(const std::chrono::seconds, std::mutex& mtx);
    void subscribe(interfaces::AbstractPlantCaretaker&);
    void operator()();

private:
    bool isAirTooDry();
    bool isSoilTooDry();
    int getAirMoisture();
    int getSoilMoisture();
};
} // namespace sensors