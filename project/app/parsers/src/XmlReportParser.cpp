#include "parsers/XmlReportParser.hpp"

#include <iostream>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include "tinyxml2/tinyxml2.h"

namespace {
template <typename T> auto getFromXml(const tinyxml2::XMLNode* node, const char* field)
{
    if (node == nullptr or node->FirstChildElement(field) == nullptr) {
        throw std::runtime_error{ "Invalid xml" };
    }

    return boost::lexical_cast<T>(node->FirstChildElement(field)->GetText());
}
} // namespace

namespace parsers {
std::optional<types::Report> XmlReportParser::parse(const std::string_view rawReport) const try {
    tinyxml2::XMLDocument doc;
    doc.Parse(rawReport.data(), rawReport.length());

    if (tinyxml2::XMLNode* root = doc.FirstChild()) {
        return types::Report{
            getFromXml<std::uint32_t>(root, "payer"),
            getFromXml<std::string>(root, "tax"),
            getFromXml<double>(root, "amount"),
            getFromXml<std::uint16_t>(root, "year"),
        };
    }

    return std::nullopt;
} catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return std::nullopt;
}
} // namespace parsers
