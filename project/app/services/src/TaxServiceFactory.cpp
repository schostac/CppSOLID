#include "services/TaxServiceFactory.hpp"

#include "parsers/JsonReportParser.hpp"
#include "parsers/XmlReportParser.hpp"
#include "services/TaxService.hpp"

namespace services {
TaxServiceFactory::TaxServiceFactory(const types::ReportFormat reportFormat)
    : reportFormat{ reportFormat }
{
}

std::unique_ptr<ITaxService> TaxServiceFactory::create() const
{
    switch (reportFormat) {
    case types::ReportFormat::Json:
        return std::make_unique<TaxService>(std::make_unique<parsers::JsonReportParser>());
    case types::ReportFormat::Xml:
        return std::make_unique<TaxService>(std::make_unique<parsers::XmlReportParser>());
    }
    return nullptr;
}
} // namespace services
