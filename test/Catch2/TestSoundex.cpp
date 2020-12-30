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
    REQUIRE_THAT(MSoundex.encode("A"), Equals("A000"));
}

TEST_CASE_METHOD(FixtureSoundex, "Pads with zeros to ensure three digits", "[SoundexEncoding]")
{
    REQUIRE_THAT(MSoundex.encode("I"), Equals("I000"));
}

TEST_CASE_METHOD(FixtureSoundex, "Replace consonants with appropriate numbers", "[SoundexEncoding]")
{
    REQUIRE_THAT(MSoundex.encode("Ax"), Equals("A200"));
}

TEST_CASE_METHOD(FixtureSoundex, "Ignore nonrecognition characters", "[SoundexEncoding]")
{
    REQUIRE_THAT(MSoundex.encode("A#"), Equals("A000"));
}

TEST_CASE_METHOD(FixtureSoundex, "Replaces multiple consonants with digits", "[SoundexEncoding]")
{
    REQUIRE_THAT(MSoundex.encode("Acdl"), Equals("A234"));
}

TEST_CASE_METHOD(FixtureSoundex, "Limits length to four characters", "[SoundexEncoding]")
{
    REQUIRE(MSoundex.encode("Dcdlb").length() == 4);
}