#include "parsers/XmlParser.hpp"

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
std::optional<types::Report> XmlParser::parseReport(const std::string& rawReport) const try {
    tinyxml2::XMLDocument doc;
    doc.Parse(rawReport.data(), rawReport.length());

    if (const tinyxml2::XMLNode* root = doc.FirstChild()) {
        return types::Report{
            getFromXml<std::uint32_t>(root, "payer"),
            getFromXml<std::string>(root, "tax"),
            getFromXml<double>(root, "amount"),
            getFromXml<std::uint16_t>(root, "year"),
        };
    }

    return std::nullopt;
} catch (const std::exception& e) {
    std::cerr << __FILE__ << ' ' << e.what() << '\n';
    return std::nullopt;
}

std::optional<types::User> XmlParser::parseCredentials(const std::string& rawCredentials) const try {
    tinyxml2::XMLDocument doc;
    doc.Parse(rawCredentials.data(), rawCredentials.length());

    if (const tinyxml2::XMLNode* root = doc.FirstChild()) {
        return types::User{
            { getFromXml<std::string>(root, "login") },
            { getFromXml<std::string>(root, "password") },
        };
    }

    return std::nullopt;
} catch (const std::exception& e) {
    std::cerr << __FILE__ << ' ' << e.what() << '\n';
    return std::nullopt;
}
} // namespace parsers
