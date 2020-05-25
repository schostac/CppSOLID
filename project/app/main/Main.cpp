#include <iostream>
#include <memory>
#include <stdexcept>

#include "configs/StartupConfig.hpp"
#include "servers/Server.hpp"
#include "services/TaxServiceFactory.hpp"

int main(int argc, char* argv[])
{
    try {
        if (const auto config = optionsToStartupConfig(argc, argv)) {
            std::cout << "Starting server on port " << config->port << '\n';
            servers::runServer(config->port, std::make_unique<services::TaxServiceFactory>(config->format));
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
