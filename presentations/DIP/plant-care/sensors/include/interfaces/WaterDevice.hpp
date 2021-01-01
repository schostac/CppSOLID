#pragma once

namespace interfaces {
class WaterDevice {
public:
    virtual ~WaterDevice() = default;

    virtual void pourWater() = 0;
    virtual void sprinkleWater() = 0;
};
} // namespace interfaces
