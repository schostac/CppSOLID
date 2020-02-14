#include "configs/StartupConfig.hpp"

#include <gtest/gtest.h>
#include <string>

#include "types/ReportFormat.hpp"

char arg0[] = "Program name";
char arg1[] = "--port";
char arg2[] = "8000";
char arg3[] = "--format";
char arg4[] = "xml";

TEST(StartupConfigTests, validOptions_returnsStartupConfig)
{
    char* argv[] = { &arg0[0], &arg1[0], &arg2[0], &arg3[0], &arg4[0], NULL };
    const auto config = optionsToStartupConfig(5, argv);
    ASSERT_TRUE(config);
    ASSERT_EQ(config->port, 8000);
    ASSERT_EQ(config->format, types::ReportFormat::Xml);
}

TEST(StartupConfigTests, helpOption_returnsEmptyStartupConfig)
{
    char help[] = "--help";
    char* argv[] = { &arg0[0], &help[0], NULL };
    const auto config = optionsToStartupConfig(2, argv);
    ASSERT_FALSE(config);
}

TEST(StartupConfigTests, notAllOptions_throws)
{
    char* argv[] = { &arg0[0], &arg1[0], &arg2[0], NULL };
    ASSERT_ANY_THROW(optionsToStartupConfig(3, argv));
}
