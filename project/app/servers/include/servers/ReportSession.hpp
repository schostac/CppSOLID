#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <optional>

#include "auth/IAuthentication.hpp"
#include "parsers/ICredentialsParser.hpp"
#include "services/ITaxServiceFactory.hpp"

using boost::asio::ip::tcp;

namespace types {
struct User;
} // namespace types

namespace servers {
class ReportSession {
public:
    ReportSession(tcp::socket, const auth::IAuthentication&, const parsers::ICredentialsParser&,
        const services::ITaxServiceFactory&);
    void start();
    void stop();

private:
    std::optional<types::User> loginUser();

    static constexpr auto MAX_LENGTH = 1024;

    tcp::socket sock;
    char data[MAX_LENGTH];

    const auth::IAuthentication& authManager;
    const parsers::ICredentialsParser& parser;
    const services::ITaxServiceFactory& taxServiceFactory;
};
} // namespace servers
