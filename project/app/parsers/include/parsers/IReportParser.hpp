#pragma once

#include <optional>
#include <string_view>

#include "types/Report.hpp"

namespace parsers {
class IReportParser {
public:
    virtual ~IReportParser() = default;
    virtual std::optional<types::Report> parseReport(const std::string_view) const = 0;
};
} // namespace parsers
