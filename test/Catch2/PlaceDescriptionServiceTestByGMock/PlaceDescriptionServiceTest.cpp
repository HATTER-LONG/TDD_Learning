#include "Http.h"
#include "PlaceDescriptionServiceMock/HttpFactory.h"
#include "PlaceDescriptionServiceMock/PlaceDescriptionService.h"
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
    static const string ValidLatitude;
    static const string ValidLongitude;

    shared_ptr<HttpStub> httpStub;
    shared_ptr<HttpFactory> factory;
    shared_ptr<PlaceDescriptionService> service;
};

TEST_CASE_METHOD(APlaceDescriptionService, "MakesHttpRequestToObtainAddress")
{
    //使用 Catch2 不需要 TearDown 主要在于每一个 SECTION 执行完成后 APlaceDescriptionService
    //都会重新析构在构造 保证各个测试之间不互相干扰
    factory = make_shared<HttpFactory>();
    service = make_shared<PlaceDescriptionService>(factory);
    httpStub = make_shared<HttpStub>();
    factory->setInstance(httpStub);

    REQUIRE(factory != nullptr);
    REQUIRE(service != nullptr);
    REQUIRE(httpStub != nullptr);

    SECTION("Check summaryDescription")
    {
        string urlStart { "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&" };
        auto expectedURL = urlStart + "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
                           "lon=" + APlaceDescriptionService::ValidLongitude;
        Expectation expect = EXPECT_CALL(*httpStub, initialize());
        EXPECT_CALL(*httpStub, get(expectedURL)).After(expect);
        service->summaryDescription(ValidLatitude, ValidLongitude);
    }
}

TEST_CASE_METHOD(APlaceDescriptionService, "FormatsRetrievedAddressIntoSummaryDescription")
{
    factory = make_shared<HttpFactory>();
    service = make_shared<PlaceDescriptionService>(factory);
    httpStub = make_shared<NiceMock<HttpStub>>();
    factory->setInstance(httpStub);

    REQUIRE(factory != nullptr);
    REQUIRE(service != nullptr);
    REQUIRE(httpStub != nullptr);

    SECTION("Check http stub get some data")
    {
        EXPECT_CALL(*httpStub, get(_))
            .WillOnce(Return(
                R"({ "address": {
              "road":"Drury Ln",
              "city":"Fountain",
              "state":"CO",
              "country":"US" }})"));

        auto description = service->summaryDescription(ValidLatitude, ValidLongitude);

        Mock::VerifyAndClearExpectations(httpStub.get());
        REQUIRE_THAT(description, Equals("Drury Ln, Fountain, CO, US"));
    }
}

const string APlaceDescriptionService::ValidLatitude("38.005");
const string APlaceDescriptionService::ValidLongitude("-104.44");
