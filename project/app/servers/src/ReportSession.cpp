#include "servers/ReportSession.hpp"

#include <iostream>
#include <stdexcept>

#include "constants/Constants.hpp"
#include "types/User.hpp"

namespace {
std::size_t read(tcp::socket& sock, char* buf, const std::size_t n)
{
    boost::system::error_code error;
    const auto readLength = sock.read_some(boost::asio::buffer(buf, n), error);
    std::cout << "Received " << readLength << " bytes\n";

    if (error == boost::asio::error::eof)
        return 0; // Connection closed cleanly by peer.
    else if (error)
        throw boost::system::system_error(error); // Some other error.

    return readLength;
}
} // namespace

namespace servers {
ReportSession::ReportSession(tcp::socket sock, const auth::IAuthentication& authManager,
    const parsers::ICredentialsParser& parser, const services::ITaxServiceFactory& taxServiceFactory)
    : sock{ std::move(sock) }
    , authManager{ authManager }
    , parser{ parser }
    , taxServiceFactory{ taxServiceFactory }
{
}

std::optional<types::User> ReportSession::loginUser()
{
    if (const auto length = read(sock, data, MAX_LENGTH)) {
        const auto user = parser.parseCredentials({ data, length });
        if (user and authManager.authenticate(user->login, user->password)) {
            return user;
        }
    }
    return std::nullopt;
}

void ReportSession::start() try {
    if (const auto user = loginUser()) {
        boost::asio::write(sock, boost::asio::buffer(constants::OK.data(), constants::OK.size()));
        for (auto taxService = taxServiceFactory.create(*user);;) {
            if (const auto length = read(sock, data, MAX_LENGTH)) {
                const auto response = taxService->onReportRequest({ data, length });
                boost::asio::write(sock, boost::asio::buffer(response.data(), response.size()));
            } else {
               return stop();
            }
        }
    } else {
        boost::asio::write(sock, boost::asio::buffer(constants::NOK.data(), constants::NOK.size()));
        stop();
        std::cerr << __FILE__ << " Failed to login a user for tax reporting\n";
    }
} catch (const std::exception& e) {
    std::cerr << __FILE__ << " " << __LINE__ << " "  << e.what() << std::endl;
}

void ReportSession::stop() try
{
    boost::system::error_code error;
    sock.shutdown(boost::asio::ip::tcp::socket::shutdown_both); // Disable sends and receives on the socket
    if (not error) {
        sock.close(error);
        if (error) {
            std::cerr << __FILE__ << " Error when closing socket " << error << '\n';
        }
    } else {
        std::cerr << __FILE__ << " Error when shutting down socket " << error << '\n';
    }
}
catch (const std::exception& e) {
    std::cerr << __FILE__ << " " << __LINE__ << " " << e.what() << std::endl;
}
} // namespace servers
