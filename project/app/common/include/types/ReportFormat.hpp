#pragma once

#include <iosfwd>

namespace types {
enum class ReportFormat { Json, Xml };
} // namespace types

std::istream& operator>>(std::istream&, types::ReportFormat&);
