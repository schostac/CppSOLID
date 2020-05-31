#pragma once

#include <memory>

#include "services/ITaxService.hpp"
#include "types/ReportFormat.hpp"
#include "types/User.hpp"

namespace services {
class ITaxServiceFactory {
public:
    virtual ~ITaxServiceFactory() = default;
    virtual std::unique_ptr<ITaxService> create(const types::User&) const = 0;
};
} // namespace services
