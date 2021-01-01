#include <iostream>
#include <stdexcept>

#include "caretaker/CactusCaretaker.hpp"

namespace caretaker {
void CactusCaretaker::pourWater() { std::cout << "Pouring water on Cactus" << std::endl; }

void CactusCaretaker::sprinkleWater() { std::cout << "Sprinkling water on Cactus" << std::endl; }
} // namespace caretaker
