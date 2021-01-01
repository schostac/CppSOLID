#pragma once
#include "interfaces/WaterDevice.hpp"

namespace caretaker {
class CactusCaretaker : public interfaces::WaterDevice {
public:
    void pourWater() override;
    void sprinkleWater() override;
};
} // namespace caretaker