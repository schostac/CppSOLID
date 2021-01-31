#include <iostream>
#include <random>
#include <thread>

#include "sensors/MoistureSensor.hpp"

namespace sensors {
MoistureSensor::MoistureSensor(const std::chrono::seconds sleepTime, std::mutex& mtx)
    : sleepTime{ sleepTime }
    , mtx{ mtx }
{
}

void MoistureSensor::subscribe(interfaces::AbstractPlantCaretaker& caretaker)
{
    caretakers.insert(&caretaker);
}

void MoistureSensor::operator()()
{
    for (;;) {
        std::unique_lock<std::mutex> lock(mtx);

        if (isAirTooDry())
            for (auto p : caretakers)
                p->sprinkleWater();
        if (isSoilTooDry())
            for (auto p : caretakers)
                p->pourWater();

        lock.unlock();
        std::this_thread::sleep_for(sleepTime);
    }
}

/* We simulate changes of moisture by generating random numbers that
 * represent the degree to which something is moisturized,
 * and then we use the threshold for sensors to trigger.
 */

bool MoistureSensor::isAirTooDry() { return getAirMoisture() < threshold; }

bool MoistureSensor::isSoilTooDry() { return getSoilMoisture() < threshold; }

int MoistureSensor::getAirMoisture()
{
    static std::mt19937 generator;
    return std::uniform_int_distribution<int>(min, max)(generator);
}

int MoistureSensor::getSoilMoisture()
{
    static std::mt19937 generator;
    return std::uniform_int_distribution<int>(min, max)(generator);
}
} // namespace sensors
