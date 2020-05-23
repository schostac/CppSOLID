#include "services/TaxService.hpp"

#include <gtest/gtest.h>
#include <string>

#include "constants/Constants.hpp"
#include "nlohmann/json.hpp"
#include "tinyxml2/tinyxml2.h"
#include "types/ReportFormat.hpp"

using namespace constants;
using json = nlohmann::json;

struct TaxServiceTests : testing::Test {
    services::TaxService sut;
};

struct JsonTaxServiceTests : TaxServiceTests {
    const types::ReportFormat format = types::ReportFormat::Json;
};

TEST_F(JsonTaxServiceTests, onJsonReportRequest_whenValidData_returnsOK)
{
    const json report = { { "payer", 1 }, { "tax", "VAT" }, { "amount", 1000 }, { "year", 2020 } };
    ASSERT_EQ(sut.onReportRequest(to_string(report), format), OK);
}

TEST_F(JsonTaxServiceTests, onJsonReportRequest_whenMissingFields_returnsNOK)
{
    const json report = { { "payer", 1 }, { "year", 2020 } };
    ASSERT_EQ(sut.onReportRequest(to_string(report), format), NOK);
}

TEST_F(JsonTaxServiceTests, onJsonReportRequest_whenEmptyReport_returnsNOK)
{
    const json report = {};
    ASSERT_EQ(sut.onReportRequest(to_string(report), format), NOK);
}

TEST_F(JsonTaxServiceTests, onJsonReportRequest_whenNumericDataInvalid_returnsNOK)
{
    const json report = { { "payer", "One" }, { "tax", "VAT" }, { "amount", "Ten" }, { "year", "Hundred" } };
    ASSERT_EQ(sut.onReportRequest(to_string(report), format), NOK);
}

struct XmlTaxServiceTests : TaxServiceTests {
    const types::ReportFormat format = types::ReportFormat::Xml;
};

TEST_F(XmlTaxServiceTests, onReportRequest_whenValidData_returnsOK)
{
    const std::string report = "<report><payer>2</payer><tax>VAT</tax><amount>10</amount><year>2020</"
                               "year></report>";
    ASSERT_EQ(sut.onReportRequest(report, format), OK);
}

TEST_F(XmlTaxServiceTests, onReportRequest_whenMissingFields_returnsNOK)
{
    const std::string report = "<report><payer>2</payer><year>2020</year></report>";
    ASSERT_EQ(sut.onReportRequest(report, format), NOK);
}

TEST_F(XmlTaxServiceTests, onReportRequest_whenEmptyReport_returnsNOK)
{
    const std::string report = "";
    ASSERT_EQ(sut.onReportRequest(report, format), NOK);
}

TEST_F(XmlTaxServiceTests, onReportRequest_whenInvalidXml_returnsNOK)
{
    const std::string report = "<<report>>";
    ASSERT_EQ(sut.onReportRequest(report, format), NOK);
}

TEST_F(XmlTaxServiceTests, onReportRequest_whenNumericDataInvalid_returnsNOK)
{
    const std::string report = "<report><payer>Two</payer><tax>VAT</tax><amount>One</"
                               "amount><year>Three</year></report>";
    ASSERT_EQ(sut.onReportRequest(report, format), NOK);
}
