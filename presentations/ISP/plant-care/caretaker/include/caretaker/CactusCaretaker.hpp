#pragma once
#include "caretaker/WaterDevice.hpp"

namespace caretaker {
class CactusCaretaker : public interfaces::WaterDevice {
public:
    void pourWater() override;
    void sprinkleWater() override;
};
} // namespace caretaker