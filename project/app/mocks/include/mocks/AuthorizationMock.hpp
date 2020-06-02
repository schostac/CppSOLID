#include "auth/IAuthorization.hpp"

#include <gmock/gmock.h>

namespace auth {
class AuthorizationMock : public IAuthorization {
public:
    MOCK_CONST_METHOD2(isAuthorized, bool(const types::Login&, std::uint32_t));
};
} // namespace auth
