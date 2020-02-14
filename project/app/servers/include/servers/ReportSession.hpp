#pragma once

#include <string>
#include <string_view>

#include <boost/asio.hpp>

#include "types/ReportFormat.hpp"
#include "services/TaxService.hpp"

using boost::asio::ip::tcp;

namespace servers
{
class ReportSession
{
public:
  ReportSession(tcp::socket, types::ReportFormat);
  void start();

private:
    std::string handleRequest(const std::string_view);

    static constexpr auto MAX_LENGTH = 1024;

    tcp::socket sock;
    const types::ReportFormat format;
    char data[MAX_LENGTH];
    services::TaxService taxService;
};
} // namespace servers

