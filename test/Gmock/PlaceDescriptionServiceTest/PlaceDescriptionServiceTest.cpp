#include "Http.h"
#include "PlaceDescriptionService/PlaceDescriptionService.h"

#include "gmock/gmock.h"
#include <gmock/gmock-matchers.h>

using namespace std;
using namespace testing;

class APlaceDescriptionService : public Test
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

    void verify(const string& Url) const { ASSERT_THAT(Url, Eq(m_expectedUrl)); }
};

TEST_F(APlaceDescriptionService, ReturnsDescriptionForValidLocation)
{
    HttpStub httpStub;
    httpStub.m_returnResponse = R"({"address": {
                                    "road":"Drury Ln",
                                    "city":"Fountain",
                                    "state":"CO",
                                    "country":"US" }})";

    string urlStart { "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&" };
    httpStub.m_expectedUrl = urlStart + "lat=" + APlaceDescriptionService::VALID_LATITUDE + "&" +
                             "lon=" + APlaceDescriptionService::VALID_LONGITUDE;

    PlaceDescriptionService service { &httpStub };
    auto description = service.summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);
    ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}