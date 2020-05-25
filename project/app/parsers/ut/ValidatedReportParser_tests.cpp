#include "parsers/ValidatedReportParser.hpp"

#include <gtest/gtest.h>
#include <optional>
#include <string>
#include <vector>

#include "constants/Constants.hpp"
#include "nlohmann/json.hpp"
#include "parsers/JsonReportParser.hpp"
#include "parsers/XmlReportParser.hpp"
#include "types/Report.hpp"

using json = nlohmann::json;

namespace parsers {
struct ValidatedReportParserTests : testing::Test {
    const ValidatedReportParser<JsonReportParser> sut;

    const std::string taxName = *constants::validTaxNames.begin();

    const std::string validReport
        = to_string(json{ { "payer", 1 }, { "tax", taxName }, { "amount", 1000 }, { "year", 2020 } });

    const std::vector<std::string> invalidReports
        = { to_string(json{ { "payer", 1 }, { "tax", taxName }, { "amount", 0.0 }, { "year", 2020 } }),
              to_string(json{ { "payer", 1 }, { "tax", taxName }, { "amount", 1000 }, { "year", 2222 } }),
              to_string(json{ { "payer", 1 }, { "tax", "Unknown tax" }, { "amount", 0 }, { "year", 2020 } }) };
};

TEST_F(ValidatedReportParserTests, reportValidationSucceeds) { ASSERT_NE(sut.parse(validReport), std::nullopt); }

TEST_F(ValidatedReportParserTests, reportValidationFails)
{
    for (const auto& invalidReport : invalidReports)
        ASSERT_EQ(sut.parse(invalidReport), std::nullopt);
}
} // namespace parsers