#pragma once

namespace types
{
struct Report;
} // namespace

namespace storage
{
class ReportsStorage
{
public:
    void storeReport(const types::Report&);
};
} // namespace storage

