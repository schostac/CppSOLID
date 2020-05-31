#include "services/TaxServiceFactory.hpp"
#include "services/TaxService.hpp"

namespace services {
TaxServiceFactory::TaxServiceFactory(
    const auth::IAuthorization& authManager, const parsers::IReportParser& reportParser)
    : authManager{ authManager }
    , reportParser{ reportParser }
{
}

std::unique_ptr<ITaxService> TaxServiceFactory::create(const types::User& user) const
{
    return std::make_unique<TaxService>(user, authManager, reportParser);
}
} // namespace services
