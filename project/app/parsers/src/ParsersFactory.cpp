#include "parsers/ParsersFactory.hpp"

#include "parsers/JsonParser.hpp"
#include "parsers/ValidatedReportParser.hpp"
#include "parsers/XmlParser.hpp"

namespace parsers {
ParsersFactory::ParsersFactory(const types::ReportFormat reportFormat)
    : reportFormat{ reportFormat }
{
}

std::unique_ptr<IReportParser> ParsersFactory::createReportParser() const
{
    switch (reportFormat) {
    case types::ReportFormat::Json:
        return std::make_unique<parsers::ValidatedReportParser<JsonParser>>();
    case types::ReportFormat::Xml:
        return std::make_unique<parsers::ValidatedReportParser<XmlParser>>();
    }

    return nullptr;
}

std::unique_ptr<ICredentialsParser> ParsersFactory::createCredentialsParser() const
{
    switch (reportFormat) {
    case types::ReportFormat::Json:
        return std::make_unique<JsonParser>();
    case types::ReportFormat::Xml:
        return std::make_unique<XmlParser>();
    }

    return nullptr;
}
} // namespace parsers