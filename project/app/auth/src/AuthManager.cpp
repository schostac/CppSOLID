#include "auth/AuthManager.hpp"

namespace {
const types::Login dummyLogin{ "John Doe" };
const types::Password dummyPassword{ "@12345" };
const std::set<std::uint32_t> dummyTaxpayerIds{ 1, 2, 3, 4, 5, 5, 6, 8, 9, 10 };
} // namespace

namespace auth {
AuthManager::AuthManager()
    : users{ types::User{ dummyLogin, dummyPassword, dummyTaxpayerIds } }
{
    // We keep one dummy user just for the purposes of this toy application.
    // In the reality, users would be registered and kept in a database.
}
bool AuthManager::authenticate(const types::Login& login, const types::Password& password) const
{
    const auto it = users.find(login);
    return it != users.end() ? it->password.value == password.value : false;
}

bool AuthManager::isAuthorized(const types::Login& login, std::uint32_t taxpayerId) const
{
    const auto it = users.find(login);
    return it != users.end() ? it->taxpayers.count(taxpayerId) != 0 : false;
}
} // namespace auth
