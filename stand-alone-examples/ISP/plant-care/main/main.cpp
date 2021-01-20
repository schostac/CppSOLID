#include <mutex>
#include <thread>

#include "caretaker/AloeCaretaker.hpp"
#include "caretaker/CactusCaretaker.hpp"
#include "sensors/MoistureSensor.hpp"
#include "sensors/SunlightSensor.hpp"

void run()
{
    std::mutex sensorsMutex;

    auto sunlightSensor = sensors::SunlightSensor(std::chrono::seconds(2), sensorsMutex);
    auto moistureSensor = sensors::MoistureSensor(std::chrono::seconds(3), sensorsMutex);

    caretaker::AloeCaretaker aloeCaretaker;
    moistureSensor.subscribe(aloeCaretaker);
    sunlightSensor.subscribe(aloeCaretaker);

    caretaker::CactusCaretaker cactusCaretaker;
    moistureSensor.subscribe(cactusCaretaker);

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