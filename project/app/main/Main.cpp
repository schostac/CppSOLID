#include <iostream>
#include <memory>
#include <stdexcept>

#include "auth/AuthManager.hpp"
#include "configs/StartupConfig.hpp"
#include "parsers/ParsersFactory.hpp"
#include "servers/Server.hpp"
#include "services/TaxServiceFactory.hpp"

int main(int argc, char* argv[])
{
    try {
        if (const auto config = optionsToStartupConfig(argc, argv)) {
            std::cout << "Starting server on port " << config->port << '\n';

            const auth::AuthManager authManager;
            const parsers::ParsersFactory parsersFactory(config->format);

            const auto credentialsParser = parsersFactory.createCredentialsParser();
            const auto reportParser = parsersFactory.createReportParser();

            const services::TaxServiceFactory taxServiceFactory(authManager, *reportParser);

            servers::runServer(config->port, authManager, *credentialsParser, taxServiceFactory);
        }
    } catch (std::exception& e) {
        std::cerr << __FILE__ << ' ' << e.what() << '\n';
        return 1;
    }

    return 0;
}
