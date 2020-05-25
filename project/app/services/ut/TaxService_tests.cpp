#include "services/TaxService.hpp"

#include <gtest/gtest.h>
#include <optional>
#include <string>

#include "ReportParserMock.hpp"
#include "constants/Constants.hpp"
#include "types/Report.hpp"

using namespace constants;
using ::testing::Return;
using ::testing::StrictMock;

struct TaxServiceTests : testing::Test {

    TaxServiceTests()
    {
        auto parserMock = std::make_unique<StrictMock<parsers::ReportParserMock>>();
        parserMockPtr = parserMock.get();
        sut = std::make_unique<services::TaxService>(std::move(parserMock));
    }

    StrictMock<parsers::ReportParserMock>* parserMockPtr;
    std::unique_ptr<services::ITaxService> sut;

    const std::string_view rawReport = "{}";
    const types::Report report{ 0, "", 0, 0 };
};

TEST_F(TaxServiceTests, whenReportParserReturnsReport_returnOK)
{
    EXPECT_CALL(*parserMockPtr, parse(rawReport)).WillOnce(Return(report));
    ASSERT_EQ(sut->onReportRequest(rawReport), OK);
}

TEST_F(TaxServiceTests, whenReportParserReturnsNull_returnNOK)
{
    EXPECT_CALL(*parserMockPtr, parse(rawReport)).WillOnce(Return(std::nullopt));
    ASSERT_EQ(sut->onReportRequest(rawReport), NOK);
}
