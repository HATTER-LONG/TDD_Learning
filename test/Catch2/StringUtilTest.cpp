#include "StringUtil.h"
#include "catch2/catch.hpp"

using namespace std;
using namespace Catch;
using namespace stringutil;


TEST_CASE("Answers head as it's First letter", "[StringUtil]")
{
    REQUIRE_THAT(head("xyz"), Equals("x"));
}

TEST_CASE("Answers head as empty when empty letter", "[StringUtil]")
{
    REQUIRE_THAT(head(""), Equals(""));
}

TEST_CASE("Answers tail as all letters after head", "[StringUtil]")
{
    REQUIRE_THAT(tail("Xyz"), Equals("yz"));
}

TEST_CASE("Answers tail as empty when empty", "[StringUtil]")
{
    REQUIRE_THAT(tail(""), Equals(""));
}

TEST_CASE("Answers tail as empty when contains only one character", "[StringUtil]")
{
    REQUIRE_THAT(tail("X"), Equals(""));
}