#include "parsers/JsonParser.hpp"

#include <gtest/gtest.h>
#include <optional>

#include "nlohmann/json.hpp"
#include "types/Report.hpp"

using json = nlohmann::json;

struct JsonParserTests : testing::Test {
    parsers::JsonParser sut;
};

TEST_F(JsonParserTests, whenValidData_parseReportReturnsReport)
{
    const json jsonReport = { { "payer", 1 }, { "tax", "VAT" }, { "amount", 1000 }, { "year", 2020 } };
    const std::optional<types::Report> parsedReport = sut.parseReport(to_string(jsonReport));
    const types::Report expectedReport{ 1, "VAT", 1000, 2020 };
    ASSERT_TRUE(parsedReport);
    ASSERT_EQ(*parsedReport, expectedReport);
}

TEST_F(JsonParserTests, whenMissingFields_parseReportReturnsNull)
{
    const json jsonReport = { { "payer", 1 }, { "year", 2020 } };
    ASSERT_EQ(sut.parseReport(to_string(jsonReport)), std::nullopt);
}

TEST_F(JsonParserTests, whenEmptyReport_parseReportReturnsNull)
{
    const json jsonReport = {};
    ASSERT_EQ(sut.parseReport(to_string(jsonReport)), std::nullopt);
}

TEST_F(JsonParserTests, whenNumericDataInvalid_parseReportReturnsNull)
{
    const json jsonReport = { { "payer", "One" }, { "tax", "VAT" }, { "amount", "Ten" }, { "year", "Hundred" } };
    ASSERT_EQ(sut.parseReport(to_string(jsonReport)), std::nullopt);
}

TEST_F(JsonParserTests, whenValidData_parseCredentialsReturnsUser)
{
    const types::User user{ { "Jhon Doe" }, { "Password" } };
    const json jsonCreds = { { "login", user.login.value }, { "password", user.password.value } };
    const std::optional<types::User> parsedUser = sut.parseCredentials(to_string(jsonCreds));
    ASSERT_TRUE(parsedUser);
    ASSERT_EQ(parsedUser->login.value, user.login.value);
    ASSERT_EQ(parsedUser->password.value, user.password.value);
}

TEST_F(JsonParserTests, whenMissingFields_parseCredentialsReturnsNull)
{
    const json jsonCreds = { { "login", "Jhon Doe" } };
    ASSERT_EQ(sut.parseCredentials(to_string(jsonCreds)), std::nullopt);
}
