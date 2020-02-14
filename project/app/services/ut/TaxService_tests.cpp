#include "services/TaxService.hpp"

#include <gtest/gtest.h>
#include <string>

#include "constants/Constants.hpp"
#include "nlohmann/json.hpp"
#include "tinyxml2/tinyxml2.h"

using namespace constants;
using json = nlohmann::json;

struct TaxServiceTests : testing::Test {
    services::TaxService sut;
};

TEST_F(TaxServiceTests, onJsonReport_returnsOK_whenValidData)
{
    const json report = { { "payer", 1 }, { "tax", "VAT" }, { "amount", 1000 }, { "year", 2020 } };
    ASSERT_EQ(sut.onJsonReport(to_string(report)), OK);
}

TEST_F(TaxServiceTests, onJsonReport_returnsNOK_whenMissingFields)
{
    const json report = { { "payer", 1 }, { "year", 2020 } };
    ASSERT_EQ(sut.onJsonReport(to_string(report)), NOK);
}

TEST_F(TaxServiceTests, onJsonReport_returnsNOK_whenEmptyReport)
{
    const json report = {};
    ASSERT_EQ(sut.onJsonReport(to_string(report)), NOK);
}

TEST_F(TaxServiceTests, onJsonReport_returnsNOK_whenNumericDataInvalid)
{
    const json report = { { "payer", "One" }, { "tax", "VAT" }, { "amount", "Ten" }, { "year", "Hundred" } };
    ASSERT_EQ(sut.onJsonReport(to_string(report)), NOK);
}

TEST_F(TaxServiceTests, onXmlReport_returnsOK_whenValidData)
{
    const std::string report = "<report><payer>2</payer><tax>VAT</tax><amount>10</amount><year>2020</year></report>";
    ASSERT_EQ(sut.onXmlReport(report), OK);
}

TEST_F(TaxServiceTests, onXmlReport_returnsNOK_whenMissingFields)
{
    const std::string report = "<report><payer>2</payer><year>2020</year></report>";
    ASSERT_EQ(sut.onXmlReport(report), NOK);
}

TEST_F(TaxServiceTests, onXmlReport_returnsNOK_whenEmptyReport)
{
    const std::string report = "";
    ASSERT_EQ(sut.onXmlReport(report), NOK);
}

TEST_F(TaxServiceTests, onXmlReport_returnsNOK_whenInvalidXml)
{
    const std::string report = "<<report>>";
    ASSERT_EQ(sut.onXmlReport(report), NOK);
}

TEST_F(TaxServiceTests, onXmlReport_returnsOK_whenNumericDataInvalid)
{
    const std::string report = "<report><payer>Two</payer><tax>VAT</tax><amount>One</amount><year>Three</year></report>";
    ASSERT_EQ(sut.onXmlReport(report), NOK);
}
