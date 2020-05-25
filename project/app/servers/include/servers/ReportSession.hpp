#pragma once

#include <boost/asio.hpp>
#include <memory>

using boost::asio::ip::tcp;

namespace services {
class ITaxService;
} // namespace services

namespace servers {
class ReportSession {
public:
    ReportSession(tcp::socket, std::unique_ptr<services::ITaxService>);
    void start();

private:
    static constexpr auto MAX_LENGTH = 1024;

    tcp::socket sock;
    char data[MAX_LENGTH];
    std::unique_ptr<services::ITaxService> taxService;
};
} // namespace servers
