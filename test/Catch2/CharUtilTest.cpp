#include "CharUtil.h"
#include "catch2/catch.hpp"

using namespace std;
using namespace Catch;
using namespace charutil;

TEST_CASE("Is a vowel for six specific letters", "[CharUtil]")
{
    REQUIRE(isVowel('A'));
    REQUIRE(isVowel('E'));
    REQUIRE(isVowel('I'));
    REQUIRE(isVowel('O'));
    REQUIRE(isVowel('U'));
    REQUIRE(isVowel('Y'));
}

TEST_CASE("Is a vowel for lower case letters", "[CharUtil]")
{
    REQUIRE(isVowel('a'));
    REQUIRE(isVowel('e'));
    REQUIRE(isVowel('i'));
    REQUIRE(isVowel('o'));
    REQUIRE(isVowel('u'));
    REQUIRE(isVowel('y'));
}

TEST_CASE("Is not a vowel for any other character", "[CharUtil]")
{
    REQUIRE_FALSE(isVowel('b'));
}

TEST_CASE("Answers appropriate upper case letter", "[CharUtil]")
{
    REQUIRE(upper('a') == 'A');
}

TEST_CASE("Handles already upper case letter", "[CharUtil]")
{
    REQUIRE(upper('B') == 'B');
}

TEST_CASE("Ignores non letter when uppercasing", "[CharUtil]")
{
    REQUIRE(upper('+') == '+');
}

TEST_CASE("Answer appropriate lower case letter", "[CharUtil]")
{
    REQUIRE(lower('A') == 'a');
}

TEST_CASE("Handles already lower case letter", "[CharUtil]")
{
    REQUIRE(lower('b') == 'b');
}

TEST_CASE("Ignores non letter when lowercasing", "[CharUtil]")
{
    REQUIRE(lower('+') == '+');
}