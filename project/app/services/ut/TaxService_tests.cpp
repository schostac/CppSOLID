#include "services/TaxService.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <optional>
#include <string>

#include "constants/Constants.hpp"
#include "mocks/AuthorizationMock.hpp"
#include "mocks/ReportParserMock.hpp"
#include "types/Report.hpp"
#include "types/User.hpp"

using namespace constants;
using ::testing::Return;
using ::testing::StrictMock;

struct TaxServiceTests : testing::Test {

    TaxServiceTests()
        : sut(user, authMock, parserMock)
    {
    }

    types::User user;
    StrictMock<auth::AuthorizationMock> authMock;
    StrictMock<parsers::ReportParserMock> parserMock;
    services::TaxService sut;

    const std::string rawReport = "{}";
    const types::Report report{ 10, "VAT", 20, 2020 };
};

TEST_F(TaxServiceTests, whenReportParsingAndAuthorizationSucceed_returnOK)
{
    EXPECT_CALL(authMock, isAuthorized(user.login, report.payer)).WillOnce(Return(true));
    EXPECT_CALL(parserMock, parseReport(rawReport)).WillOnce(Return(report));
    ASSERT_EQ(sut.onReportRequest(rawReport), OK);
}

TEST_F(TaxServiceTests, whenReportParsingFails_returnNOK)
{
    EXPECT_CALL(parserMock, parseReport(rawReport)).WillOnce(Return(std::nullopt));
    EXPECT_CALL(authMock, isAuthorized(user.login, report.payer)).Times(0);
    ASSERT_EQ(sut.onReportRequest(rawReport), NOK);
}

TEST_F(TaxServiceTests, whenAuthorizationFails_returnNOK)
{
    EXPECT_CALL(parserMock, parseReport(rawReport)).WillOnce(Return(report));
    EXPECT_CALL(authMock, isAuthorized(user.login, report.payer)).WillOnce(Return(false));
    ASSERT_EQ(sut.onReportRequest(rawReport), NOK);
}
