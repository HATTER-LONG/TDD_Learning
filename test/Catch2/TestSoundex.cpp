#include "Soundex.h"
#include "catch2/catch.hpp"
#include "spdlog/spdlog.h"
using namespace Catch;

class FixtureSoundex
{
public:
    Soundex MSoundex;
};

TEST_CASE_METHOD(FixtureSoundex, "Retain sole letter of one letter world", "[SoundexEncoding]")
{
    GIVEN("A MSoundex member")
    {
        WHEN("Input one char")
        {
            auto encoded = MSoundex.encode("A");
            THEN("Check that the return value is correct") { REQUIRE_THAT(encoded, Equals("A000")); }
        }
    }
}

TEST_CASE_METHOD(FixtureSoundex, "Pads with zeros to ensure three digits", "[SoundexEncoding]")
{
    GIVEN("A MSoundex member")
    {
        WHEN("Input one char")
        {
            auto encoded = MSoundex.encode("I");
            THEN("Check that the return value pads with zeros") { REQUIRE_THAT(encoded, Equals("I000")); }
        }
    }
}

TEST_CASE_METHOD(FixtureSoundex, "Retains sole letter of one letter word")
{
    GIVEN("A MSoundex member")
    {
        WHEN("Enter a word")
        {
            auto encoded = MSoundex.encode("Ab");
            THEN("Check that the return value Retains sole letter of one letter word") { REQUIRE_THAT(encoded, Equals("A100")); }
        }
    }
}