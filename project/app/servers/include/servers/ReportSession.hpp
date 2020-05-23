#pragma once

#include <string>
#include <string_view>

#include <boost/asio.hpp>
#include <memory>

#include "services/ITaxService.hpp"
#include "types/ReportFormat.hpp"

using boost::asio::ip::tcp;

namespace servers {
class ReportSession {
public:
    ReportSession(tcp::socket, types::ReportFormat, std::unique_ptr<services::ITaxService>);
    void start();

private:
    static constexpr auto MAX_LENGTH = 1024;

    tcp::socket sock;
    const types::ReportFormat format;
    char data[MAX_LENGTH];
    std::unique_ptr<services::ITaxService> taxService;
};
} // namespace servers
