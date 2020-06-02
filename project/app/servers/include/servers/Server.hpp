#pragma once

#include <cstdint>
#include <memory>

#include "auth/IAuthentication.hpp"
#include "parsers/ICredentialsParser.hpp"
#include "services/ITaxServiceFactory.hpp"

namespace servers {
using Port = std::uint16_t;

void runServer(
    Port, const auth::IAuthentication&, const parsers::ICredentialsParser&, const services::ITaxServiceFactory&);
} // namespace servers
