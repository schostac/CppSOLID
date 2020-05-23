#pragma once

#include <cstdint>
#include <iostream>
#include <optional>

#include <boost/program_options.hpp>

#include "types/ReportFormat.hpp"

namespace po = boost::program_options;

struct StartupConfig {
    const std::uint16_t port;
    const types::ReportFormat format;
};

std::optional<const StartupConfig> optionsToStartupConfig(int argc, char* argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()("help", "Produce help message")("port", po::value<std::uint16_t>(), "Set server port")(
        "format", po::value<types::ReportFormat>(), "Set tax report format (json or xml)");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return std::nullopt;
    }

    return StartupConfig{ vm["port"].as<std::uint16_t>(), vm["format"].as<types::ReportFormat>() };
}
