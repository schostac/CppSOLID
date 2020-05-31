#pragma once

#include <optional>
#include <string_view>

#include "types/User.hpp"

namespace parsers {
class ICredentialsParser {
public:
    virtual ~ICredentialsParser() = default;
    virtual std::optional<types::User> parseCredentials(const std::string_view) const = 0;
};
} // namespace parsers
