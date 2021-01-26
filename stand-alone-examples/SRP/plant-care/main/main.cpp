#include <mutex>
#include <thread>

#include "caretaker/PlantCaretaker.hpp"
#include "sensors/MoistureSensor.hpp"
#include "sensors/SunlightSensor.hpp"

void run()
{
    std::mutex sensorsMutex;

    auto sunlightSensor = sensors::SunlightSensor(std::chrono::seconds(2), sensorsMutex);
    auto moistureSensor = sensors::MoistureSensor(std::chrono::seconds(3), sensorsMutex);

    caretaker::PlantCaretaker plantCaretaker1;
    moistureSensor.subscribe(plantCaretaker1);
    sunlightSensor.subscribe(plantCaretaker1);

    caretaker::PlantCaretaker plantCaretaker2;
    moistureSensor.subscribe(plantCaretaker2);

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