#pragma once

#include <string>
#include <string_view>

#include "storage/ReportsStorage.hpp"

namespace services
{
class TaxService {
public:
    std::string onJsonReport(const std::string_view);
    std::string onXmlReport(const std::string_view);
private:
    storage::ReportsStorage storage;
};
} // namespace serivces
