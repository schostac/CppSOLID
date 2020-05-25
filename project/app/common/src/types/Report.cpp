#include "types/Report.hpp"

#include <tuple>

namespace types {
bool operator==(const Report& lhs, const Report& rhs)
{
    return std::tie(lhs.payer, lhs.tax, lhs.amount, lhs.year) == std::tie(rhs.payer, rhs.tax, rhs.amount, rhs.year);
}
} // namespace types
