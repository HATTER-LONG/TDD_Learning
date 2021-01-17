#include "PlaceDescriptionService/AddressExtractor.h"
#include "catch2/catch.hpp"

#include <algorithm>
#include <string>
using namespace std;
using namespace Catch;

class AnAddressExtractor
{
public:
    AddressExtractor Extractor;
};

class IsAddressEmpty : public Catch::MatcherBase<Address>
{
public:
    IsAddressEmpty() { }
    bool match(Address const& Arg) const override
    {
        return Arg.Road.empty() && Arg.City.empty() && Arg.State.empty() && Arg.Country.empty();
    }

    virtual std::string describe() const override { return "is empty about  Address Info"; }
};

TEST_CASE_METHOD(AnAddressExtractor, "ReturnsAnEmptyAddressOnAFailedParse", "AnAddressExtractor")
{
    auto address = Extractor.addressFrom("not valid json");

    REQUIRE_THAT(address, IsAddressEmpty());
}

TEST_CASE_METHOD(AnAddressExtractor, "ReturnsAnEmptyAddressWhenNoAddressFound", "AnAddressExtractor")
{
    const auto* json = R"({ "place_id":"15331615" })";

    auto address = Extractor.addressFrom(json);

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

    auto address = Extractor.addressFrom(json);

    REQUIRE_THAT(address.Road, Equals("War Eagle Court"));
    REQUIRE_THAT(address.City, Equals("Colorado Springs"));
    REQUIRE_THAT(address.State, Equals("Colorado"));
    REQUIRE_THAT(address.Country, Equals("United States of America"));
}

TEST_CASE_METHOD(AnAddressExtractor, "DefaultsNonexistentFieldsToEmpty", "AnAddressExtractor")
{
    const auto* json = R"({
         "address":{
            "road":"War Eagle Court",
            "city":"Colorado Springs",
            "country":"United States of America" }})";

    auto address = Extractor.addressFrom(json);

    REQUIRE_THAT(address.State, Equals(""));
}
