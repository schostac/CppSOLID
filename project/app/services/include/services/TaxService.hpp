#pragma once

#include "ITaxService.hpp"

#include <memory>

#include "storage/ReportsStorage.hpp"

namespace parsers {
class IReportParser;
} // namespace parsers

namespace services {
class TaxService : public ITaxService {
public:
    TaxService(std::unique_ptr<parsers::IReportParser>);
    ReportStatus onReportRequest(const std::string_view) override;

private:
    std::unique_ptr<parsers::IReportParser> reportParser;
    storage::ReportsStorage storage;
};
} // namespace services
