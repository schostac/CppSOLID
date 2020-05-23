#pragma once

#include <cstdint>

namespace types {
enum class ReportFormat;
} // namespace types

namespace servers {
using Port = std::uint16_t;

void runServer(Port, types::ReportFormat);
} // namespace servers
