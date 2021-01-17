#include "PlaceDescriptionServiceMock/CurlHttp.h"
#include "catch2/catch.hpp"

#include <string>

using namespace Catch;
using namespace std;

TEST_CASE("WriteCallback", "Http")
{
    string buffer("123456789012");
    size_t size(12);
    size_t numberOfMembers(1);
    CurlHttp::writeCallback("123456789012", size, numberOfMembers, NULL);
    REQUIRE_THAT(CurlHttp::response(), Equals("123456789012"));
}

TEST_CASE("DISABLED_Get", "[.]HttpIntegration")
{
    CurlHttp http;
    http.initialize();
    auto response = http.get("http://langrsoft.com");
    REQUIRE_THAT(response, Contains("Jeff Langr"));
}
