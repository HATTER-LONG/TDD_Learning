#include "Http.h"
#include "PlaceDescriptionServiceMock/PlaceDescriptionService.h"

#include "gmock/gmock.h"
#include <gmock/gmock-generated-function-mockers.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock-spec-builders.h>
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
    static const string ValidLatitude;
    static const string ValidLongitude;
};

const string APlaceDescriptionService::ValidLatitude("38.005");
const string APlaceDescriptionService::ValidLongitude("-104.44");

class PlaceDescriptionServiceStubHttpService : public PlaceDescriptionService
{
public:
    PlaceDescriptionServiceStubHttpService(shared_ptr<HttpStub> ParmHttpStub)
            : HttpStub { ParmHttpStub }
    {
    }
    shared_ptr<Http> httpService() const override { return HttpStub; }
    shared_ptr<Http> HttpStub;
};



TEST_F(APlaceDescriptionService, ReturnsDescriptionForValidLocation)
{
    shared_ptr<HttpStub> httpStub { new HttpStub };
    string urlStart { "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&" };
    auto expectedURL = urlStart + "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
                       "lon=" + APlaceDescriptionService::ValidLongitude;

    Expectation Expectations = EXPECT_CALL(*httpStub, initialize());
    //  get(expectedURL) 这一步同时验证了应该传给 get 的参数与 expectedURL 一致
    EXPECT_CALL(*httpStub, get(expectedURL)).After(Expectations);

    PlaceDescriptionServiceStubHttpService service { httpStub };
    service.summaryDescription(ValidLatitude, ValidLongitude);
}

TEST_F(APlaceDescriptionService, FormatsRetrievedAddressIntoSummaryDescription)
{
    shared_ptr<HttpStub> httpStub { new NiceMock<HttpStub> };

    EXPECT_CALL(*httpStub, get(_))
        .WillOnce(Return(
            R"({ "address": {
              "road":"Drury Ln",
              "city":"Fountain",
              "state":"CO",
              "country":"US" }})"));
    PlaceDescriptionServiceStubHttpService service(httpStub);

    auto description = service.summaryDescription(ValidLatitude, ValidLongitude);

    ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
