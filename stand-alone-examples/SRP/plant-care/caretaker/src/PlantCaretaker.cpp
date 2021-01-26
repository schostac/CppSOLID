#include <iostream>

#include "caretaker/PlantCaretaker.hpp"

namespace caretaker {
void PlantCaretaker::pourWater() { std::cout << "Pouring water on Aloe" << std::endl; }

void PlantCaretaker::sprinkleWater() { std::cout << "Sprinkling water on Aloe" << std::endl; }

void PlantCaretaker::openWindowBlinds()
{
    if (not windowBlindsOpen) {
        windowBlindsOpen = true;
        std::cout << "Opened window blinds for Aloe" << std::endl;
    }
}

void PlantCaretaker::closeWindowBlinds()
{
    if (windowBlindsOpen) {
        windowBlindsOpen = false;
        std::cout << "Closed window blinds for Aloe" << std::endl;
    }
}
} // namespace caretaker
