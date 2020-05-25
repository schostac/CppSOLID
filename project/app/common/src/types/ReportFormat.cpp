#include "types/ReportFormat.hpp"

#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>

std::istream& operator>>(std::istream& in, types::ReportFormat& format)
{
    std::string token;
    in >> token;

    boost::algorithm::to_lower(token);

    if (token == "json")
        format = types::ReportFormat::Json;
    else if (token == "xml")
        format = types::ReportFormat::Xml;
    else
        in.setstate(std::ios_base::failbit);

    return in;
}
