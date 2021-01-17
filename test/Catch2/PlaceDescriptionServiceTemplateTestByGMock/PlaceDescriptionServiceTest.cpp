#include "Http.h"
#include "PlaceDescriptionServiceTemplateMock/PlaceDescriptionService.h"
#include "catch2/catch.hpp"

#include "gmock/gmock.h"
#include <memory>

using namespace std;
using namespace testing;
using namespace Catch;
;
class HttpStub : public Http
{
public:
    MOCK_METHOD(void, initialize, (), (override));
    MOCK_METHOD(string, get, (const string&), (const override));
};

class APlaceDescriptionService
{
public:
    static const string ValidLatitude;
    static const string ValidLongitude;
};

class APlaceDescriptionServiceWithHttpMock : public APlaceDescriptionService
{
public:
    PlaceDescriptionServiceTemplate<HttpStub> service;
};

TEST_CASE_METHOD(APlaceDescriptionServiceWithHttpMock, "MakesHttpRequestToObtainAddress")
{
    string urlStart { "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&" };

    auto expectedURL = urlStart + "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
                       "lon=" + APlaceDescriptionService::ValidLongitude;
    EXPECT_CALL(service.http(), initialize());
    EXPECT_CALL(service.http(), get(expectedURL));

    service.summaryDescription(ValidLatitude, ValidLongitude);
}

class APlaceDescriptionServiceWithNiceHttpMock : public APlaceDescriptionService
{
public:
    PlaceDescriptionServiceTemplate<NiceMock<HttpStub>> service;
};

TEST_CASE_METHOD(APlaceDescriptionServiceWithNiceHttpMock, "FormatsRetrievedAddressIntoSummaryDescription")
{
    EXPECT_CALL(service.http(), get(_))
        .WillOnce(Return(
            R"({ "address": {
              "road":"Drury Ln",
              "city":"Fountain",
              "state":"CO",
              "country":"US" }})"));

    auto description = service.summaryDescription(ValidLatitude, ValidLongitude);

    REQUIRE_THAT(description, Equals("Drury Ln, Fountain, CO, US"));
}


const string APlaceDescriptionService::ValidLatitude("38.005");
const string APlaceDescriptionService::ValidLongitude("-104.44");
