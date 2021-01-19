#pragma once

#include <string>
#include <string_view>

#include "types/ReportFormat.hpp"

namespace services {
using ReportStatus = std::string;

class ITaxService {
public:
    virtual ~ITaxService() = default;
    virtual ReportStatus onReportRequest(const std::string) = 0;
};
} // namespace services
