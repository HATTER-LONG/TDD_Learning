#include "Http.h"
#include "PlaceDescriptionServiceMock/HttpFactory.h"
#include "PlaceDescriptionServiceMock/PlaceDescriptionService.h"

#include "gmock/gmock.h"
#include <memory>

using namespace std;
using namespace testing;

class HttpStub : public Http
{
public:
    MOCK_METHOD(void, initialize, (), (override));
    MOCK_METHOD(string, get, (const string&), (const override));
};

class APlaceDescriptionService : public Test
{
public:
    static const string VALID_LATITUDE;
    static const string VALID_LONGITUDE;

    shared_ptr<HttpStub> m_httpStub;
    shared_ptr<HttpFactory> m_factory;
    shared_ptr<PlaceDescriptionService> m_service;

    virtual void SetUp() override
    {
        m_factory = make_shared<HttpFactory>();
        m_service = make_shared<PlaceDescriptionService>(m_factory);
    }

    void TearDown() override
    {
        m_factory.reset();
        m_httpStub.reset();
    }
};

class APlaceDescriptionServiceWithHttpMock : public APlaceDescriptionService
{
public:
    void SetUp() override
    {
        APlaceDescriptionService::SetUp();
        m_httpStub = make_shared<HttpStub>();
        m_factory->setInstance(m_httpStub);
    }
};

TEST_F(APlaceDescriptionServiceWithHttpMock, MakesHttpRequestToObtainAddress)
{
    string urlStart { "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&" };
    auto expectedURL = urlStart + "lat=" + APlaceDescriptionService::VALID_LATITUDE + "&" +
                       "lon=" + APlaceDescriptionService::VALID_LONGITUDE;
    EXPECT_CALL(*m_httpStub, initialize());
    EXPECT_CALL(*m_httpStub, get(expectedURL));
    m_service->summaryDescription(VALID_LATITUDE, VALID_LONGITUDE);
}

class APlaceDescriptionServiceWithNiceHttpMock : public APlaceDescriptionService
{
public:
    void SetUp() override
    {
        APlaceDescriptionService::SetUp();
        m_httpStub = make_shared<NiceMock<HttpStub>>();
        m_factory->setInstance(m_httpStub);
    }
};

TEST_F(APlaceDescriptionServiceWithNiceHttpMock, FormatsRetrievedAddressIntoSummaryDescription)
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
    ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}

const string APlaceDescriptionService::VALID_LATITUDE("38.005");
const string APlaceDescriptionService::VALID_LONGITUDE("-104.44");
