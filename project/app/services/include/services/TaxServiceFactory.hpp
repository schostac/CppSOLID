#pragma once

#include "services/ITaxServiceFactory.hpp"

namespace services {
class TaxServiceFactory : public ITaxServiceFactory {
public:
    TaxServiceFactory(types::ReportFormat);
    std::unique_ptr<ITaxService> create() const override;

private:
    const types::ReportFormat reportFormat;
};
} // namespace services
