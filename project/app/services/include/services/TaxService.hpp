#pragma once

#include "ITaxService.hpp"

#include <optional>

#include "storage/ReportsStorage.hpp"
#include "types/Report.hpp"

namespace services {
class TaxService : public ITaxService {
public:
    ReportStatus onReportRequest(const std::string_view, const types::ReportFormat) override;

private:
    ReportStatus handleReport(const std::optional<types::Report>&);
    storage::ReportsStorage storage;
};
} // namespace services
