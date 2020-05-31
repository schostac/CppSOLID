#pragma once

#include "types/User.hpp"

namespace auth {
class IAuthentication {
public:
    virtual ~IAuthentication() = default;
    virtual bool authenticate(const types::Login&, const types::Password&) const = 0;
};
} // namespace auth
