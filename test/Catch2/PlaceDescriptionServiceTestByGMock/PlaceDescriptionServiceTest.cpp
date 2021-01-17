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
    static const string VALID_LATITUDE;
    static const string VALID_LONGITUDE;

    shared_ptr<HttpStub> m_httpStub;
    shared_ptr<HttpFactory> m_factory;
    shared_ptr<PlaceDescriptionService> m_service;
};

TEST_CASE_METHOD(APlaceDescriptionService, "MakesHttpRequestToObtainAddress")
{
    //使用 Catch2 不需要 TearDown 主要在于每一个 SECTION 执行完成后 APlaceDescriptionService
    //都会重新析构在构造 保证各个测试之间不互相干扰
    m_factory = make_shared<HttpFactory>();
    m_service = make_shared<PlaceDescriptionService>(m_factory);
    m_httpStub = make_shared<HttpStub>();
    m_factory->setInstance(m_httpStub);

    REQUIRE(m_factory != nullptr);
    REQUIRE(m_service != nullptr);
    REQUIRE(m_httpStub != nullptr);

    SECTION("Check summaryDescription")
    {
        string urlStart { "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&" };
        auto expectedURL = urlStart + "lat=" + APlaceDescriptionService::VALID_LATITUDE + "&" +
                           "lon=" + APlaceDescriptionService::VALID_LONGITUDE;
        Expectation expect = EXPECT_CALL(*m_httpStub, initialize());
        EXPECT_CALL(*m_httpStub, get(expectedURL)).After(expect);
        m_service->summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);
    }
}

TEST_CASE_METHOD(APlaceDescriptionService, "FormatsRetrievedAddressIntoSummaryDescription")
{
    m_factory = make_shared<HttpFactory>();
    m_service = make_shared<PlaceDescriptionService>(m_factory);
    m_httpStub = make_shared<NiceMock<HttpStub>>();
    m_factory->setInstance(m_httpStub);

    REQUIRE(m_factory != nullptr);
    REQUIRE(m_service != nullptr);
    REQUIRE(m_httpStub != nullptr);

    SECTION("Check http stub get some data")
    {
        EXPECT_CALL(*m_httpStub, get(_))
            .WillOnce(Return(
                R"({ "address": {
              "road":"Drury Ln",
              "city":"Fountain",
              "state":"CO",
              "country":"US" }})"));

        auto description = m_service->summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);

        Mock::VerifyAndClearExpectations(m_httpStub.get());
        REQUIRE_THAT(description, Equals("Drury Ln, Fountain, CO, US"));
    }
}

const string APlaceDescriptionService::VALID_LATITUDE("38.005");
const string APlaceDescriptionService::VALID_LONGITUDE("-104.44");
