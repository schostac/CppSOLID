#pragma once

namespace caretaker {
class PlantCaretaker {
    bool windowBlindsOpen = true;

public:
    void pourWater();
    void sprinkleWater();

    void openWindowBlinds();
    void closeWindowBlinds();
};
} // namespace caretaker