#pragma once

#include "parsers/IReportParser.hpp"

namespace parsers {
class JsonReportParser : public IReportParser {
public:
    std::optional<types::Report> parse(const std::string_view) const override;
};
} // namespace parsers
