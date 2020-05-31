#include "auth/AuthManager.hpp"

namespace {
const types::Login dummyLogin{ "Jhon Doe" };
const types::Password dummyPassword{ "@12345" };
const std::set<std::uint32_t> dummyTaxIds{ 1, 2, 3, 4, 5, 5, 6, 8, 9, 10 };
} // namespace

namespace auth {
AuthManager::AuthManager()
    : users{ types::User{ dummyLogin, dummyPassword, dummyTaxIds } }
{
    // We keep one dummy user just for the purposes of this toy application.
    // In the reality, users would be registered and kept in a databse.
}
bool AuthManager::authenticate(const types::Login& login, const types::Password& password) const
{
    const auto it = users.find(login);
    return it != users.end() ? it->password.value == password.value : false;
}

bool AuthManager::isAuthorized(const types::Login& login, std::uint32_t taxPayerId) const
{
    const auto it = users.find(login);
    return it != users.end() ? it->taxpayers.count(taxPayerId) != 0 : false;
}
} // namespace auth
