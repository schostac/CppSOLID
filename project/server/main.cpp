#include <iostream>
#include <thread>
#include <string>
#include <string_view>
#include <array>
#include <cstdint>

#include <boost/asio.hpp>

#include "external/nlohmann/json.hpp"
#include "external/tinyxml2/tinyxml2.h"

using boost::asio::ip::tcp;
using json = nlohmann::json;

const int MAX_LENGTH = 1024;
constexpr std::array<const char*, 4> EXPECTED_FIELDS = { "payer", "tax", "amount", "year" };

enum class ReportFormat
{
  Json,
  Xml
};

class ReportingSession
{
  tcp::socket sock;
  const ReportFormat format;
  char data[MAX_LENGTH];

public:
  ReportingSession(tcp::socket sock, ReportFormat format)
    : sock{ std::move(sock) }
    , format{ format }
  {
  }

  void start() try 
  {
    for (;;) 
    {
      boost::system::error_code error;
      const auto length = sock.read_some(boost::asio::buffer(data), error);
      
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      const auto response = handleRequest({ data, length });
      boost::asio::write(sock, boost::asio::buffer(response.data(), response.size()));
    }
  }
  catch (const std::exception& e) 
  {
    std::cerr << e.what() << "\n";
  }

private:

  std::string handleRequest(const std::string_view request) try 
  {
    switch (format) 
    {
      case ReportFormat::Json:
        return handleJsonRequest(request);
      case ReportFormat::Xml:
        return handleXmlRequest(request);
    }

    return "NOK";
  } 
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return "NOK";
  }

  std::string handleJsonRequest(const std::string_view request)
  {
    auto json = nlohmann::json::parse(request);

    if(json.empty())
      return "NOK";

    for (const auto& field : EXPECTED_FIELDS)
      if (json[field].empty())
        return "NOK";

    return "OK";
  }

  std::string handleXmlRequest(const std::string_view request)
  {
    tinyxml2::XMLDocument doc;
    doc.Parse(request.data());
    tinyxml2::XMLNode* root = doc.FirstChild();

    if (root == nullptr)
      return "NOK";

    for (const auto& field : EXPECTED_FIELDS)
      if (root->FirstChildElement(field) == nullptr)
        return "NOK";

    return "OK";
  }
};

void server(boost::asio::io_context& io_context, std::uint16_t port, ReportFormat format)
{
  tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
  for (;;) 
  {
    std::thread(&ReportingSession::start, ReportingSession(a.accept(), format)).detach();
  }
}

int main(int argc, char* argv[])
{
  try 
  {
    if (argc != 3) 
    {
      std::cerr << "Expected args: <port> <format>\n";
      return 1;
    }

    std::cout << "Starting server. Report format " << argv[2] << '\n';

    boost::asio::io_context io_context;
    const auto format = std::strcmp(argv[2], "json") == 0 ? ReportFormat::Json : ReportFormat::Xml;
    server(io_context, std::atoi(argv[1]), format);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << "\n";
  }

  return 0;
}
