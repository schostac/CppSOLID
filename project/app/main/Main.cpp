#include <iostream>
#include <stdexcept>

#include "configs/StartupConfig.hpp"
#include "servers/Server.hpp"

int main(int argc, char* argv[])
{
    try {
        if (const auto config = optionsToStartupConfig(argc, argv)) {
            std::cout << "Starting server on port " << config->port << '\n';
            servers::runServer(config->port, config->format);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
