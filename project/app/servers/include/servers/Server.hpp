#pragma once

#include <cstdint>
#include <memory>

namespace services {
class ITaxServiceFactory;
} // namespace services

namespace servers {
using Port = std::uint16_t;

void runServer(Port, std::unique_ptr<services::ITaxServiceFactory>);
} // namespace servers
