#pragma once

#include "types/User.hpp"

namespace auth {
class IAuthorization {
public:
    virtual ~IAuthorization() = default;
    virtual bool isAuthorized(const types::Login&, std::uint32_t) const = 0;
};
} // namespace auth
