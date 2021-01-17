#include "Http.h"
#include "PlaceDescriptionService/PlaceDescriptionService.h"
#include "catch2/catch.hpp"

#include <algorithm>

using namespace std;
using namespace Catch;

class APlaceDescriptionService
{
public:
    static const string ValidLatitude;
    static const string ValidLongitude;
};

const string APlaceDescriptionService::ValidLatitude("38.005");
const string APlaceDescriptionService::ValidLongitude("-104.44");

class HttpStub : public Http
{
public:
    string ReturnResponse;
    string ExpectedURL;
    void initialize() override { }
    std::string get(const std::string& Url) const override
    {
        verify(Url);
        return ReturnResponse;
    }

    void verify(const string& Url) const { REQUIRE_THAT(Url, Equals(ExpectedURL)); }
};

TEST_CASE_METHOD(APlaceDescriptionService, "ReturnsDescriptionForValidLocation", "APlaceDescriptionService")
{
    HttpStub httpStub;
    httpStub.ReturnResponse = R"({"address": {
                                    "road":"Drury Ln",
                                    "city":"Fountain",
                                    "state":"CO",
                                    "country":"US" }})";

    string urlStart { "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&" };
    httpStub.ExpectedURL = urlStart + "lat=" + ValidLatitude + "&" + "lon=" + ValidLongitude;

    PlaceDescriptionService service { &httpStub };
    auto description = service.summaryDescription(ValidLatitude, ValidLongitude);
    REQUIRE_THAT(description, Equals("Drury Ln, Fountain, CO, US"));
}