#include "parsers/IReportParser.hpp"

#include <gmock/gmock.h>

namespace parsers {
class ReportParserMock : public IReportParser {
public:
    MOCK_CONST_METHOD1(parseReport, std::optional<types::Report>(const std::string&));
};
} // namespace parsers
