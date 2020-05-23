#include "servers/ReportSession.hpp"

#include <iostream>
#include <stdexcept>

#include "constants/Constants.hpp"

namespace servers {
ReportSession::ReportSession(
    tcp::socket sock, const types::ReportFormat format, std::unique_ptr<services::ITaxService> taxService)
    : sock{ std::move(sock) }
    , format{ format }
    , taxService{ std::move(taxService) }
{
    if (this->taxService == nullptr)
        throw std::runtime_error{ "Tax service not provided" };
}

void ReportSession::start() try {
    for (;;) {
        boost::system::error_code error;
        const auto length = sock.read_some(boost::asio::buffer(data), error);
        std::cout << length << std::endl;

        if (error == boost::asio::error::eof)
            break; // Connection closed cleanly by peer.
        else if (error)
            throw boost::system::system_error(error); // Some other error.

        const auto response = taxService->onReportRequest({ data, length }, format);
        boost::asio::write(sock, boost::asio::buffer(response.data(), response.size()));
    }
} catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
}
} // namespace servers
