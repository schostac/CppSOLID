#pragma once

#include <optional>
#include <string>

#include "types/Report.hpp"

namespace parsers {
class IReportParser {
public:
    virtual ~IReportParser() = default;
    virtual std::optional<types::Report> parseReport(const std::string&) const = 0;
};
} // namespace parsers
