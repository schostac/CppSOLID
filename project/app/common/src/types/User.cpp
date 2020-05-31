#include "types/User.hpp"

namespace types {
bool operator==(const Login& lhs, const Login& rhs) { return lhs.value == rhs.value; }

bool operator<(const User& lhs, const User& rhs) { return lhs.login.value < rhs.login.value; }

bool operator<(const User& a, const Login& l) { return a.login.value < l.value; }

bool operator<(const Login& l, const User& u) { return l.value < u.login.value; }
} // namespace types
