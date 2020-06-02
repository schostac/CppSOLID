#include "parsers/XmlParser.hpp"

#include <gtest/gtest.h>
#include <optional>
#include <string>

#include "types/Report.hpp"

struct XmlParserTests : testing::Test {
    parsers::XmlParser sut;
};

TEST_F(XmlParserTests, whenValidData_parseReportReturnsReport)
{
    const std::string xmlReport = "<report><payer>2</payer><tax>VAT</tax><amount>10</amount>"
                                  "<year>2020</year></report>";
    const std::optional<types::Report> parsedReport = sut.parseReport(xmlReport);
    const types::Report expectedReport{ 2, "VAT", 10, 2020 };
    ASSERT_TRUE(parsedReport);
    ASSERT_EQ(*parsedReport, expectedReport);
}

TEST_F(XmlParserTests, whenMissingFields_parseReportReturnsNull)
{
    const std::string xmlReport = "<report><payer>2</payer><year>2020</year></report>";
    ASSERT_EQ(sut.parseReport(xmlReport), std::nullopt);
}

TEST_F(XmlParserTests, whenEmptyReport_parseReportReturnsNull)
{
    const std::string xmlReport = "";
    ASSERT_EQ(sut.parseReport(xmlReport), std::nullopt);
}

TEST_F(XmlParserTests, whenInvalidXml_parseReportReturnsNull)
{
    const std::string xmlReport = "<<report>>";
    ASSERT_EQ(sut.parseReport(xmlReport), std::nullopt);
}

TEST_F(XmlParserTests, whenNumericDataInvalid_parseReportReturnsNull)
{
    const std::string xmlReport = "<report><payer>Two</payer><tax>VAT</tax><amount>One"
                                  "</amount><year>Three</year></report>";
    ASSERT_EQ(sut.parseReport(xmlReport), std::nullopt);
}

TEST_F(XmlParserTests, whenValidData_parseCredentialsReturnsUser)
{
    const std::string xmlReport = "<credentials><login>Jhon Doe</login>"
                                  "<password>123</password></credentials>";
    const std::optional<types::User> parsedUser = sut.parseCredentials(xmlReport);
    ASSERT_TRUE(parsedUser);
    ASSERT_EQ(parsedUser->login.value, std::string("Jhon Doe"));
    ASSERT_EQ(parsedUser->password.value, std::string("123"));
}

TEST_F(XmlParserTests, whenMissingFields_parseCredentialsReturnsNull)
{
    const std::string xmlReport = "<credentials><login>Jhon Doe</login></credentials>";
    const std::optional<types::User> parsedUser = sut.parseCredentials(xmlReport);
    ASSERT_EQ(parsedUser, std::nullopt);
}