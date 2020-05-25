#include "services/TaxService.hpp"

#include "constants/Constants.hpp"
#include "parsers/IReportParser.hpp"

namespace services {
TaxService::TaxService(std::unique_ptr<parsers::IReportParser> reportParser)
    : reportParser{ std::move(reportParser) }
{
    if (this->reportParser == nullptr)
        throw std::runtime_error{ "Unexpected null report parser" };
}

ReportStatus TaxService::onReportRequest(const std::string_view request)
{
    if (const auto report = reportParser->parse(request); report != std::nullopt) {
        storage.storeReport(*report);
        return constants::OK;
    }
    return constants::NOK;
}
} // namespace services
