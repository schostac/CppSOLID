#include "parsers/JsonReportParser.hpp"

#include <iostream>
#include <stdexcept>

#include "nlohmann/json.hpp"

namespace parsers {
std::optional<types::Report> JsonReportParser::parse(const std::string_view rawReport) const try {
    if (const auto json = nlohmann::json::parse(rawReport); not json.empty()) {
        return types::Report{ json.at("payer"), json.at("tax"), json.at("amount"), json.at("year") };
    }

    return std::nullopt;
} catch (const std::exception& e) {
    std::cerr << __FILE__ << ' ' << e.what() << '\n';
    return std::nullopt;
}
} // namespace parsers
