#include "services/TaxService.hpp"

#include <iostream>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include "constants/Constants.hpp"
#include "nlohmann/json.hpp"
#include "tinyxml2/tinyxml2.h"
#include "types/Report.hpp"

using namespace constants;

namespace {
template <typename T>
auto getFromXml(const tinyxml2::XMLNode* node, const char* field)
{
    if (node == nullptr or node->FirstChildElement(field) == nullptr)
        throw std::runtime_error{ "Invalid xml" };

    return boost::lexical_cast<T>(node->FirstChildElement(field)->GetText());
}
} // namespace

namespace services {
std::string TaxService::onJsonReport(const std::string_view report) try {
    auto json = nlohmann::json::parse(report);

    if (json.empty())
        return NOK;

    storage.storeReport(types::Report{ json.at("payer"), json.at("tax"), json.at("amount"), json.at("year") });

    return OK;
} catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return NOK;
}

std::string TaxService::onXmlReport(const std::string_view report) try {
    tinyxml2::XMLDocument doc;
    doc.Parse(report.data());
    tinyxml2::XMLNode* root = doc.FirstChild();

    if (root == nullptr)
        return NOK;

    storage.storeReport(
        types::Report{
            getFromXml<std::uint32_t>(root, "payer"),
            getFromXml<std::string>(root, "tax"),
            getFromXml<double>(root, "amount"),
            getFromXml<std::uint16_t>(root, "year"),
        });

    return OK;
} catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return NOK;
}
} // namespace services
