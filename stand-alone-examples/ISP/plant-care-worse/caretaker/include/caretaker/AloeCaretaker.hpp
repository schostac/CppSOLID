#pragma once
#include "caretaker/AbstractPlantCaretaker.hpp"

namespace caretaker {
class AloeCaretaker : public interfaces::AbstractPlantCaretaker {
    bool windowBlindsOpen = true;

public:
    void pourWater() override;
    void sprinkleWater() override;

    void openWindowBlinds() override;
    void closeWindowBlinds() override;
};
} // namespace caretaker