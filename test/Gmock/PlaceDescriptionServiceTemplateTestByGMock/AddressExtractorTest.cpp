#include "PlaceDescriptionService/AddressExtractor.h"

#include "gmock/gmock.h"
#include <algorithm>
#include <string>

using namespace std;
using namespace testing;

class AnAddressExtractor : public Test
{
public:
    AddressExtractor m_extractor;
};

MATCHER(IsAddressEmpty, "")
{
    return arg.m_road.empty() && arg.m_city.empty() && arg.m_state.empty() && arg.m_country.empty();
}

TEST_F(AnAddressExtractor, ReturnsAnEmptyAddressOnAFailedParse)
{
    auto address = m_extractor.addressFrom("not valid json");

    ASSERT_THAT(address, IsAddressEmpty());
}

TEST_F(AnAddressExtractor, ReturnsAnEmptyAddressWhenNoAddressFound)
{
    const auto* json = R"({ "place_id":"15331615" })";

    auto address = m_extractor.addressFrom(json);

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

    auto address = m_extractor.addressFrom(json);

    ASSERT_THAT(address.m_road, Eq("War Eagle Court"));
    ASSERT_THAT(address.m_city, Eq("Colorado Springs"));
    ASSERT_THAT(address.m_state, Eq("Colorado"));
    ASSERT_THAT(address.m_country, Eq("United States of America"));
}

TEST_F(AnAddressExtractor, DefaultsNonexistentFieldsToEmpty)
{
    const auto* json = R"({
         "address":{
            "road":"War Eagle Court",
            "city":"Colorado Springs",
            "country":"United States of America" }})";

    auto address = m_extractor.addressFrom(json);

    ASSERT_THAT(address.m_state, Eq(""));
}
