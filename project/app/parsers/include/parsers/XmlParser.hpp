#pragma once

#include "parsers/ICredentialsParser.hpp"
#include "parsers/IReportParser.hpp"

namespace parsers {
class XmlParser : public IReportParser, public ICredentialsParser {
public:
    std::optional<types::Report> parseReport(const std::string&) const override;
    std::optional<types::User> parseCredentials(const std::string&) const override;
};
} // namespace parsers
