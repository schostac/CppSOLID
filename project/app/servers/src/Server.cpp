#include "servers/Server.hpp"

#include <boost/asio.hpp>
#include <memory>
#include <thread>

#include "servers/ReportSession.hpp"

using boost::asio::ip::tcp;

namespace servers {
void runServer(const Port port, const auth::IAuthentication& authManager,
    const parsers::ICredentialsParser& credentialsParser, const services::ITaxServiceFactory& taxtServiceFactory)
{
    boost::asio::io_context io_context;
    tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));

    for (;;) {
        std::thread(
            &ReportSession::start, ReportSession(a.accept(), authManager, credentialsParser, taxtServiceFactory))
            .detach();
    }
}
} // namespace servers
