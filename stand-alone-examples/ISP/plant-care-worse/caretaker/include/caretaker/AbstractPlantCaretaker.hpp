#pragma once

namespace interfaces {
class AbstractPlantCaretaker {
public:
    virtual ~AbstractPlantCaretaker() = default;

    virtual void pourWater() = 0;
    virtual void sprinkleWater() = 0;

    virtual void openWindowBlinds() = 0;
    virtual void closeWindowBlinds() = 0;
};
} // namespace interfaces
