#pragma once

namespace interfaces {
class WindowDevice {
public:
    virtual ~WindowDevice() = default;

    virtual void openWindowBlinds() = 0;
    virtual void closeWindowBlinds() = 0;
};
} // namespace interfaces
