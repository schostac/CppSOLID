#include "servers/ReportSession.hpp"

#include <iostream>
#include <stdexcept>

#include "constants/Constants.hpp"

namespace servers {
ReportSession::ReportSession(tcp::socket sock, const types::ReportFormat format)
    : sock{ std::move(sock) }
    , format{ format }
{
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

        const auto response = handleRequest({ data, length });
        boost::asio::write(sock, boost::asio::buffer(response.data(), response.size()));
    }
} catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
}

std::string ReportSession::handleRequest(const std::string_view request) try {
    switch (format) {
    case types::ReportFormat::Json:
        return taxService.onJsonReport(request);
    case types::ReportFormat::Xml:
        return taxService.onXmlReport(request);
    }

    return constants::NOK;
} catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return constants::NOK;
}
} // namespace servers
