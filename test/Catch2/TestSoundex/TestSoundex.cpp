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

TEST_CASE_METHOD(FixtureSoundex, "Ignores Vowel like letters", "[SoundexEncoding]")
{
    REQUIRE_THAT(MSoundex.encode("BaAeEiIoOuUhHyYcdl"), Equals("B234"));
}

TEST_CASE_METHOD(FixtureSoundex, "Combines duplicate encodings", "[SoundexEncoding]")
{
    // REQUIRE_THAT(MSoundex.encodedDigit('b'), Equals(MSoundex.encodedDigit('f')));
    // REQUIRE_THAT(MSoundex.encodedDigit('c'), Equals(MSoundex.encodedDigit('g')));
    // REQUIRE_THAT(MSoundex.encodedDigit('d'), Equals(MSoundex.encodedDigit('t')));

    REQUIRE_THAT(MSoundex.encode("Abfcgdt"), Equals("A123"));
}

TEST_CASE_METHOD(FixtureSoundex, "Upper cases first letter", "[SoundexEncoding]")
{
    REQUIRE_THAT(MSoundex.encode("abcd"), StartsWith("A"));
}

TEST_CASE_METHOD(FixtureSoundex, "Ignores case when encoding consonants", "[SoundexEncoding]")
{
    REQUIRE_THAT(MSoundex.encode("BCDL"), Equals(MSoundex.encode("Bcdl")));
}

TEST_CASE_METHOD(FixtureSoundex, "Combines duplicate codes when 2nd letter duplicates 1st", "[SoundexEncoding]")
{
    REQUIRE_THAT(MSoundex.encode("Bbcd"), Equals("B230"));
}

TEST_CASE_METHOD(FixtureSoundex, "Does not combine duplicate encodings separate by vowels")
{
    REQUIRE_THAT(MSoundex.encode("Jbob"), Equals("J110"));
}