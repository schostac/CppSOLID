#pragma once

#include <cstdint>
#include <set>
#include <string>

namespace types {
struct Login {
    const std::string value;
};

struct Password {
    const std::string value; // kept hashed in real applications
};

struct User {
    const Login login;
    const Password password;
    const std::set<std::uint32_t> taxpayers; // tax payers' ids on behalf of which the user can submit reports
};

bool operator==(const Login&, const Login&);
bool operator<(const User&, const User&);
bool operator<(const User&, const Login&);
bool operator<(const Login&, const User&);
} // namespace types
