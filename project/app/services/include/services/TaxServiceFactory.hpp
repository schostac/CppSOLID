#pragma once

#include "auth/IAuthorization.hpp"
#include "parsers/IReportParser.hpp"
#include "services/ITaxServiceFactory.hpp"

namespace services {
class TaxServiceFactory : public ITaxServiceFactory {
public:
    TaxServiceFactory(const auth::IAuthorization&, const parsers::IReportParser&);
    std::unique_ptr<ITaxService> create(const types::User&) const override;

private:
    const auth::IAuthorization& authManager;
    const parsers::IReportParser& reportParser;
};
} // namespace services
