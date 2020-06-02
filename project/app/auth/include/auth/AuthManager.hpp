#pragma once

#include "auth/IAuthentication.hpp"
#include "auth/IAuthorization.hpp"

#include <functional>
#include <set>

#include "types/User.hpp"

namespace auth {
class AuthManager : public IAuthentication, public IAuthorization {
public:
    AuthManager();
    bool authenticate(const types::Login&, const types::Password&) const override;
    bool isAuthorized(const types::Login&, std::uint32_t) const override;

private:
    std::set<types::User, std::less<>> users;
};
} // namespace auth
