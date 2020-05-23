#pragma once

namespace types {
struct Report;
} // namespace types

namespace storage {
class ReportsStorage {
public:
    void storeReport(const types::Report&);
};
} // namespace storage
