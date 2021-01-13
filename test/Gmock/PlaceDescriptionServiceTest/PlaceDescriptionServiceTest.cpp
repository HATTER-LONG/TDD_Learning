#include "Http.h"
#include "PlaceDescriptionService/PlaceDescriptionService.h"

#include "gmock/gmock.h"
#include <gmock/gmock-matchers.h>

using namespace std;
using namespace testing;

class APlaceDescriptionService : public Test
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

    void verify(const string& Url) const { ASSERT_THAT(Url, Eq(ExpectedURL)); }
};

TEST_F(APlaceDescriptionService, ReturnsDescriptionForValidLocation)
{
    HttpStub httpStub;
    httpStub.ReturnResponse = R"({"address": {
                                    "road":"Drury Ln",
                                    "city":"Fountain",
                                    "state":"CO",
                                    "country":"US" }})";

    string urlStart { "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&" };
    httpStub.ExpectedURL = urlStart + "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
                           "lon=" + APlaceDescriptionService::ValidLongitude;

    PlaceDescriptionService service { &httpStub };
    auto description = service.summaryDescription(ValidLatitude, ValidLongitude);
    ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}