#include "Http.h"
#include "PlaceDescriptionService/PlaceDescriptionService.h"
#include "catch2/catch.hpp"

#include <algorithm>

using namespace std;
using namespace Catch;

class APlaceDescriptionService
{
public:
    static const string VALID_LATITUDE;
    static const string VALID_LONGITUDE;
};

const string APlaceDescriptionService::VALID_LATITUDE("38.005");
const string APlaceDescriptionService::VALID_LONGITUDE("-104.44");

class HttpStub : public Http
{
public:
    string m_returnResponse;
    string m_expectedUrl;
    void initialize() override { }
    std::string get(const std::string& Url) const override
    {
        verify(Url);
        return m_returnResponse;
    }

    void verify(const string& Url) const { REQUIRE_THAT(Url, Equals(m_expectedUrl)); }
};

TEST_CASE_METHOD(APlaceDescriptionService, "ReturnsDescriptionForValidLocation", "APlaceDescriptionService")
{
    HttpStub httpStub;
    httpStub.m_returnResponse = R"({"address": {
                                    "road":"Drury Ln",
                                    "city":"Fountain",
                                    "state":"CO",
                                    "country":"US" }})";

    string urlStart { "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&" };
    httpStub.m_expectedUrl = urlStart + "lat=" + VALID_LATITUDE + "&" + "lon=" + VALID_LONGITUDE;

    PlaceDescriptionService service { &httpStub };
    auto description = service.summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);
    REQUIRE_THAT(description, Equals("Drury Ln, Fountain, CO, US"));
}