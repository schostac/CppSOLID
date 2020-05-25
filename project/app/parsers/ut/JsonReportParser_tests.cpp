#include "parsers/JsonReportParser.hpp"

#include <gtest/gtest.h>
#include <optional>

#include "nlohmann/json.hpp"
#include "types/Report.hpp"

using json = nlohmann::json;

struct JsonReportParserTests : testing::Test {
    parsers::JsonReportParser sut;
};

TEST_F(JsonReportParserTests, whenValidData_returnsReport)
{
    const json jsonReport = { { "payer", 1 }, { "tax", "VAT" }, { "amount", 1000 }, { "year", 2020 } };
    const std::optional<types::Report> parsedReport = sut.parse(to_string(jsonReport));
    const types::Report expectedReport{ 1, "VAT", 1000, 2020 };
    ASSERT_TRUE(parsedReport);
    ASSERT_EQ(*parsedReport, expectedReport);
}

TEST_F(JsonReportParserTests, whenMissingFields_returnsNull)
{
    const json jsonReport = { { "payer", 1 }, { "year", 2020 } };
    ASSERT_EQ(sut.parse(to_string(jsonReport)), std::nullopt);
}

TEST_F(JsonReportParserTests, whenEmptyReport_returnsNull)
{
    const json jsonReport = {};
    ASSERT_EQ(sut.parse(to_string(jsonReport)), std::nullopt);
}

TEST_F(JsonReportParserTests, whenNumericDataInvalid_returnsNull)
{
    const json jsonReport = { { "payer", "One" }, { "tax", "VAT" }, { "amount", "Ten" }, { "year", "Hundred" } };
    ASSERT_EQ(sut.parse(to_string(jsonReport)), std::nullopt);
}
