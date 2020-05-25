#include "parsers/XmlReportParser.hpp"

#include <gtest/gtest.h>
#include <optional>
#include <string>

#include "types/Report.hpp"

struct XmlReportParserTests : testing::Test {
    parsers::XmlReportParser sut;
};

TEST_F(XmlReportParserTests, whenValidData_returnsReport)
{
    const std::string xmlReport = "<report><payer>2</payer><tax>VAT</tax><amount>10</amount>"
                                  "<year>2020</year></report>";
    const std::optional<types::Report> parsedReport = sut.parse(xmlReport);
    const types::Report expectedReport{ 2, "VAT", 10, 2020 };
    ASSERT_TRUE(parsedReport);
    ASSERT_EQ(*parsedReport, expectedReport);
}

TEST_F(XmlReportParserTests, whenMissingFields_returnsNull)
{
    const std::string xmlReport = "<report><payer>2</payer><year>2020</year></report>";
    ASSERT_EQ(sut.parse(xmlReport), std::nullopt);
}

TEST_F(XmlReportParserTests, whenEmptyReport_returnsNull)
{
    const std::string xmlReport = "";
    ASSERT_EQ(sut.parse(xmlReport), std::nullopt);
}

TEST_F(XmlReportParserTests, whenInvalidXml_returnsNull)
{
    const std::string xmlReport = "<<report>>";
    ASSERT_EQ(sut.parse(xmlReport), std::nullopt);
}

TEST_F(XmlReportParserTests, whenNumericDataInvalid_returnsNull)
{
    const std::string xmlReport = "<report><payer>Two</payer><tax>VAT</tax><amount>One"
                                  "</amount><year>Three</year></report>";
    ASSERT_EQ(sut.parse(xmlReport), std::nullopt);
}
