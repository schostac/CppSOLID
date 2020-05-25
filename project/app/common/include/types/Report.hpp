#pragma once

#include <cstdint>
#include <string>

namespace types {
struct Report {
    const std::uint32_t payer;
    const std::string tax;
    const double amount;
    const std::uint16_t year;
};

bool operator==(const Report&, const Report&);
} // namespace types
