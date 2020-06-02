#pragma once

#include <memory>

#include "parsers/ICredentialsParser.hpp"
#include "parsers/IReportParser.hpp"

namespace parsers {
class IParsersFactory {
public:
    virtual ~IParsersFactory() = default;
    virtual std::unique_ptr<IReportParser> createReportParser() const = 0;
    virtual std::unique_ptr<ICredentialsParser> createCredentialsParser() const = 0;
};
} // namespace services
