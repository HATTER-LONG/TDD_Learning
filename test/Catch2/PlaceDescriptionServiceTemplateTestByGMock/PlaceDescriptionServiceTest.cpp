#include "Http.h"
#include "PlaceDescriptionServiceTemplateMock/PlaceDescriptionService.h"
#include "catch2/catch.hpp"

#include "gmock/gmock.h"
#include <memory>

using namespace std;
using namespace testing;
using namespace Catch;

class HttpStub : public Http
{
public:
    MOCK_METHOD(void, initialize, (), (override));
    MOCK_METHOD(string, get, (const string&), (const override));
};

class APlaceDescriptionService
{
public:
    static const string VALID_LATITUDE;
    static const string VALID_LONGITUDE;
};

class APlaceDescriptionServiceWithHttpMock : public APlaceDescriptionService
{
public:
    PlaceDescriptionServiceTemplate<HttpStub> m_service;
};

TEST_CASE_METHOD(APlaceDescriptionServiceWithHttpMock, "MakesHttpRequestToObtainAddress")
{
    string urlStart { "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&" };

    auto expectedURL = urlStart + "lat=" + APlaceDescriptionService::VALID_LATITUDE + "&" +
                       "lon=" + APlaceDescriptionService::VALID_LONGITUDE;
    EXPECT_CALL(m_service.http(), initialize());
    EXPECT_CALL(m_service.http(), get(expectedURL));

    m_service.summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);
}

class APlaceDescriptionServiceWithNiceHttpMock : public APlaceDescriptionService
{
public:
    PlaceDescriptionServiceTemplate<NiceMock<HttpStub>> m_service;
};

TEST_CASE_METHOD(APlaceDescriptionServiceWithNiceHttpMock, "FormatsRetrievedAddressIntoSummaryDescription")
{
    EXPECT_CALL(m_service.http(), get(_))
        .WillOnce(Return(
            R"({ "address": {
              "road":"Drury Ln",
              "city":"Fountain",
              "state":"CO",
              "country":"US" }})"));

    auto description = m_service.summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);

    REQUIRE_THAT(description, Equals("Drury Ln, Fountain, CO, US"));
}


const string APlaceDescriptionService::VALID_LATITUDE("38.005");
const string APlaceDescriptionService::VALID_LONGITUDE("-104.44");
