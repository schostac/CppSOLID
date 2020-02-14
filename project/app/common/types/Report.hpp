#pragma once

#include <string>
#include <cstdint>

namespace types
{
struct Report
{
  const std::uint32_t payer;
  const std::string tax;
  const double amount;
  const std::uint16_t year;
};
} // namespace types
