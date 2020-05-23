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
template <typename T> auto getFromXml(const tinyxml2::XMLNode* node, const char* field)
{
    if (node == nullptr or node->FirstChildElement(field) == nullptr) {
        throw std::runtime_error{ "Invalid xml" };
    }

    return boost::lexical_cast<T>(node->FirstChildElement(field)->GetText());
}

std::optional<types::Report> extractReportFromJson(const std::string_view report)
{
    if (auto json = nlohmann::json::parse(report); not json.empty()) {
        return types::Report{ json.at("payer"), json.at("tax"), json.at("amount"), json.at("year") };
    }

    return std::nullopt;
}

std::optional<types::Report> extractReportFromXml(const std::string_view report)
{
    tinyxml2::XMLDocument doc;
    doc.Parse(report.data());

    if (tinyxml2::XMLNode* root = doc.FirstChild(); root != nullptr) {
        return types::Report{
            getFromXml<std::uint32_t>(root, "payer"),
            getFromXml<std::string>(root, "tax"),
            getFromXml<double>(root, "amount"),
            getFromXml<std::uint16_t>(root, "year"),
        };
    }

    return std::nullopt;
}
} // namespace

namespace services {
ReportStatus TaxService::onReportRequest(const std::string_view request, const types::ReportFormat format) try {
    switch (format) {
    case types::ReportFormat::Json:
        return handleReport(extractReportFromJson(request));
    case types::ReportFormat::Xml:
        return handleReport(extractReportFromXml(request));
    default:
        throw std::runtime_error{ "Unexpected report format" };
    }
} catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return constants::NOK;
}

ReportStatus TaxService::handleReport(const std::optional<types::Report>& report)
{
    if (report != std::nullopt) {
        storage.storeReport(*report);
        return constants::OK;
    }
    return constants::NOK;
}
} // namespace services
