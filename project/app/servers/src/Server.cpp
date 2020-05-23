#include "servers/Server.hpp"

#include <boost/asio.hpp>
#include <memory>
#include <thread>

#include "servers/ReportSession.hpp"
#include "services/TaxService.hpp"
#include "types/ReportFormat.hpp"

using boost::asio::ip::tcp;

namespace servers {
void runServer(const Port port, const types::ReportFormat format)
{
    boost::asio::io_context io_context;
    tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
    for (;;) {
        std::thread(&ReportSession::start, ReportSession(a.accept(), format, std::make_unique<services::TaxService>()))
            .detach();
    }
}
} // namespace servers
