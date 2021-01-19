#pragma once

#include "services/ITaxService.hpp"

#include <memory>

#include "auth/IAuthorization.hpp"
#include "parsers/IReportParser.hpp"
#include "storage/ReportsStorage.hpp"
#include "types/User.hpp"

namespace services {
class TaxService : public ITaxService {
public:
    TaxService(const types::User&, const auth::IAuthorization&, const parsers::IReportParser&);
    ReportStatus onReportRequest(const std::string) override;

private:
    const types::User& user;
    const auth::IAuthorization& authManager;
    const parsers::IReportParser& reportParser;
    storage::ReportsStorage storage;
};
} // namespace services
