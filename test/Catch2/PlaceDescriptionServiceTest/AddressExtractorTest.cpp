#include "PlaceDescriptionService/AddressExtractor.h"
#include "catch2/catch.hpp"

#include <algorithm>
#include <string>
using namespace std;
using namespace Catch;

class AnAddressExtractor
{
public:
    AddressExtractor m_extractor;
};

class IsAddressEmpty : public Catch::MatcherBase<Address>
{
public:
    IsAddressEmpty() { }
    bool match(Address const& Arg) const override
    {
        return Arg.m_road.empty() && Arg.m_city.empty() && Arg.m_state.empty() && Arg.m_country.empty();
    }

    virtual std::string describe() const override { return "is empty about  Address Info"; }
};

TEST_CASE_METHOD(AnAddressExtractor, "ReturnsAnEmptyAddressOnAFailedParse", "AnAddressExtractor")
{
    auto address = m_extractor.addressFrom("not valid json");

    REQUIRE_THAT(address, IsAddressEmpty());
}

TEST_CASE_METHOD(AnAddressExtractor, "ReturnsAnEmptyAddressWhenNoAddressFound", "AnAddressExtractor")
{
    const auto* json = R"({ "place_id":"15331615" })";

    auto address = m_extractor.addressFrom(json);

    REQUIRE_THAT(address, IsAddressEmpty());
}

TEST_CASE_METHOD(AnAddressExtractor, "ReturnsPopulatedAddressForValidJsonResult", "AnAddressExtractor")
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

    REQUIRE_THAT(address.m_road, Equals("War Eagle Court"));
    REQUIRE_THAT(address.m_city, Equals("Colorado Springs"));
    REQUIRE_THAT(address.m_state, Equals("Colorado"));
    REQUIRE_THAT(address.m_country, Equals("United States of America"));
}

TEST_CASE_METHOD(AnAddressExtractor, "DefaultsNonexistentFieldsToEmpty", "AnAddressExtractor")
{
    const auto* json = R"({
         "address":{
            "road":"War Eagle Court",
            "city":"Colorado Springs",
            "country":"United States of America" }})";

    auto address = m_extractor.addressFrom(json);

    REQUIRE_THAT(address.m_state, Equals(""));
}
