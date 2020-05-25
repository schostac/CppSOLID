#pragma once

#include "parsers/IReportParser.hpp"

namespace parsers {
class XmlReportParser : public IReportParser {
public:
    std::optional<types::Report> parse(const std::string_view) const override;
};
} // namespace parsers
