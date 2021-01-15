#include "Http.h"
#include "PlaceDescriptionServiceMock/PlaceDescriptionService.h"

#include "gmock/gmock.h"
#include <gmock/gmock-generated-function-mockers.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock-spec-builders.h>

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
    MOCK_METHOD(void, initialize, (), (override));
    MOCK_METHOD(string, get, (const string&), (const override));
};

TEST_F(APlaceDescriptionService, ReturnsDescriptionForValidLocation)
{
    HttpStub httpStub;
    string urlStart { "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&" };
    auto expectedURL = urlStart + "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
                       "lon=" + APlaceDescriptionService::ValidLongitude;

    EXPECT_CALL(httpStub, initialize());
    EXPECT_CALL(httpStub, get(expectedURL));
    PlaceDescriptionService service { &httpStub };
    service.summaryDescription(ValidLatitude, ValidLongitude);
}