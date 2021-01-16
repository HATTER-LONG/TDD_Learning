#include "PlaceDescriptionService/AddressExtractor.h"

#include "gmock/gmock.h"
#include <algorithm>
#include <string>

using namespace std;
using namespace testing;

class AnAddressExtractor : public Test
{
public:
    AddressExtractor Extractor;
};

MATCHER(IsAddressEmpty, "")
{
    return arg.Road.empty() && arg.City.empty() && arg.State.empty() && arg.Country.empty();
}

TEST_F(AnAddressExtractor, ReturnsAnEmptyAddressOnAFailedParse)
{
    auto address = Extractor.addressFrom("not valid json");

    ASSERT_THAT(address, IsAddressEmpty());
}

TEST_F(AnAddressExtractor, ReturnsAnEmptyAddressWhenNoAddressFound)
{
    const auto* json = R"({ "place_id":"15331615" })";

    auto address = Extractor.addressFrom(json);

    ASSERT_THAT(address, IsAddressEmpty());
}

TEST_F(AnAddressExtractor, ReturnsPopulatedAddressForValidJsonResult)
{
    const auto* json = R"({
         "place_id":"15331615",
         "address":{
            "road":"War Eagle Court",
            "city":"Colorado Springs",
            "state":"Colorado",
            "country":"United States of America",
         }
      })";

    auto address = Extractor.addressFrom(json);

    ASSERT_THAT(address.Road, Eq("War Eagle Court"));
    ASSERT_THAT(address.City, Eq("Colorado Springs"));
    ASSERT_THAT(address.State, Eq("Colorado"));
    ASSERT_THAT(address.Country, Eq("United States of America"));
}

TEST_F(AnAddressExtractor, DefaultsNonexistentFieldsToEmpty)
{
    const auto* json = R"({
         "address":{
            "road":"War Eagle Court",
            "city":"Colorado Springs",
            "country":"United States of America" }})";

    auto address = Extractor.addressFrom(json);

    ASSERT_THAT(address.State, Eq(""));
}
