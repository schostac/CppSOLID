#pragma once

#include <cstdint>
#include <optional>

#include "types/ReportFormat.hpp"

struct StartupConfig {
    const std::uint16_t port;
    const types::ReportFormat format;
};

std::optional<const StartupConfig> optionsToStartupConfig(int argc, char* argv[]);
