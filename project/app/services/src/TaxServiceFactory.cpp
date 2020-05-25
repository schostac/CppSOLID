#include "services/TaxServiceFactory.hpp"

#include "parsers/JsonReportParser.hpp"
#include "parsers/ValidatedReportParser.hpp"
#include "parsers/XmlReportParser.hpp"
#include "services/TaxService.hpp"

namespace services {
TaxServiceFactory::TaxServiceFactory(const types::ReportFormat reportFormat)
    : reportFormat{ reportFormat }
{
}

std::unique_ptr<ITaxService> TaxServiceFactory::create() const
{
    using JsonParser = parsers::ValidatedReportParser<parsers::JsonReportParser>;
    using XmlParser = parsers::ValidatedReportParser<parsers::XmlReportParser>;

    switch (reportFormat) {
    case types::ReportFormat::Json:
        return std::make_unique<TaxService>(std::make_unique<JsonParser>());
    case types::ReportFormat::Xml:
        return std::make_unique<TaxService>(std::make_unique<XmlParser>());
    }

    return nullptr;
}
} // namespace services
